/* $Id: P2_mmap.c,v 45.3 1997/09/29 03:50:04 jthomas Exp $ */
/* Copyright (C) 1997, The University of Texas at Austin. */

/* mmap() Memory Manager */

/* Note that the parameter f to all mmap procedures is the file number
   (the hash of the mmap_file name).  By making all the mmap static
   variables arrays indexed by f, we are able to have up to
   MAX_MMAP_FILE mmap files open concurrently (assuming no hash
   clash).  f is computed statically by ddlhint in x/mmap.xp1 and used
   in paces/P2_mmap.c (JAT) */

/*****************************************************************************/
/*                  Includes.                                                */
/*****************************************************************************/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "P2_paces.h"                   /* BOOLEAN */

#include <assert.h>                     /* assert() */
#include <fcntl.h>                      /* open() */
#include <stddef.h>                     /* NULL */
#include <sys/mman.h>                   /* mmap() */
#include <sys/stat.h>                   /* open(), fstat() */
#include <sys/types.h>                  /* open(), fstat() */
#include <unistd.h>                     /* unlink() */

#include "lex.h"                        /* MAX_IDENT_LEN */
#include "mmap.h"                       /* MAX_MMAP_FILE */
#include "P2_mmap.h"                    /* POINTER */

/*****************************************************************************/
/*                  Constants and Macros.                                    */
/*****************************************************************************/

#define MAX_MMAP_VAR 100                 /* Maximum mmap variables. */
#define MAGIC_PATTERN 0x1234             /* Magic pattern. */
  
#define MAX_MMAP_VAR_NAME_LEN 100

/* Also defined in x/log.xp */
/* Round up X to the nearest multiple of C. */
#if 1
#define ROUNDUP(X, C) ((((X - 1) / (C)) + 1) * (C))
#else
/* (Only works for C equal to a power of 2). */
#define ROUNDUP(X, C) ((X) & (C-1))? ((X + (C-1)) & ~(C-1)) : (X)
#endif

/* Vaild mmap address? */
#define MMAP_ADDRESS_LOW(X, F) \
  (((void *) X) < ((mmap_header[F])->base))
#define MMAP_ADDRESS_HIGH(X, F) \
  (((void *) X) >= ((mmap_header[F])->base + (mmap_header[F])->size))
#define MMAP_ADDRESS_VALID(X, F) \
  (!MMAP_ADDRESS_LOW(X, F) && !MMAP_ADDRESS_HIGH(X, F))

/* Valid mmap variable name? */
/* name length must be > 0 and < MAX_MMAP_VAR_NAME_LEN.
   name can (and often does) contain non-alphabetic characters. */
#define MMAP_VAR_NAME_VALID(S) \
  ((S)[0] != '\0' && strlen(S) < MAX_MMAP_VAR_NAME_LEN)

/* Valid mmap file descriptor? */
#define MMAP_FD_VALID(FD) ((FD) > 2)

/*****************************************************************************/
/*                  Typedefs.                                                */
/*****************************************************************************/

typedef struct {
  BOOLEAN in_use;                        /* is variable in use */
  void    *p;                            /* pointer to mmap variable */
  char    name[MAX_MMAP_VAR_NAME_LEN];   /* variable name */
} MMAP_VAR;

typedef struct {
  int      magic_pattern;                /* magic pattern */
  int      size;                         /* size of mmap memory in bytes */
  void     *base;                        /* mmap base address */
  void     *free;                        /* first free address of memory */
  char     filename[MAX_IDENT_LEN];      /* Name of mmap file. */
  MMAP_VAR v[MAX_MMAP_VAR];              /* actual array of mmap variables */
} MMAP_HEADER;

/*****************************************************************************/
/*                  Static variables.                                        */
/*****************************************************************************/

/* Handle to mmap file. */
static int mmap_fd[MAX_MMAP_FILE];     

/* TRUE if mmap file is already opened (by this process).  FALSE otherwise. */
static BOOLEAN mmap_file_open[MAX_MMAP_FILE];

/* Pointer to the mmap header.  The mmap header itself is stored in
   mmap mamory. */
static MMAP_HEADER *mmap_header[MAX_MMAP_FILE];

/*****************************************************************************/
/*                  Open memory.                                             */
/*****************************************************************************/

/* Make sure that the given region does not overlap any existing mmap region. */

static void
assert_mmap_region_valid (void *base, int size, const char *filename, int f)
{
  int i;
  /* For each existing region. */
  for (i = 0; i < MAX_MMAP_FILE; i++)
    if (i != f && mmap_header[i] != 0)
    {
      /* Error if given region is not above existing region
         and existing region is not above given region. */
      if (!(((unsigned) base)
            >= (((unsigned) mmap_header[i]->base) + mmap_header[i]->size))
          && !(((unsigned) mmap_header[i]->base)
               >= (((unsigned) base) + size)))
        P2_runtime_error("mmap regions overlap for files \"%s\" and \"%s\"",
                         filename, (mmap_header[i])->filename);
    }
}

/* If it does not already exists, create a mmap file
   called "filename".  Return file descriptior of mmap file. */
/* Note: size_in_bytes is the SUGGESTED size of the mmap memory, we
   will add on the mmap header and round up to the nearest page
   boundry to get the ACTUAL size of the mmap memory. */

int
P2_open_mmap_memory (const char *filename, int size_in_bytes,
                     BOOLEAN persistent, int f)
{
  int         header_size; /* Size of header in pages,
                              rounded up to full page boundary. */
  int         region_size; /* Size of data region in bytes, 
                              rounded up to full page boundary. */
  int         total_size;  /* Size of persistent region in bytes. */
  MMAP_HEADER file_header; /* Buffer to store header read from file. */
  void        *base;       /* Base address */
  struct stat fstat_buf;   /* fstat places information into this structure */
  int         oflag;
  int         i;

  assert(f >= 0 && f < MAX_MMAP_FILE);
  assert(size_in_bytes >= 0);
  assert(persistent == 0 || persistent == 1);

  /* Add on header and round up to the nearest page boundary. */
  header_size = ROUNDUP(sizeof(MMAP_HEADER), SYSTEM_PAGE_SIZE);
  region_size = ROUNDUP(size_in_bytes, SYSTEM_PAGE_SIZE);
  total_size  = header_size + region_size;

  /* Make sure declared size is (at least) larger than header size. */
  if (total_size <= header_size)
    P2_runtime_error("mmap file \"%s\" size %d too small even for header",
                     filename, total_size);

  /* Make sure that filename is valid. */
  if (filename[0] == '\0')
    P2_runtime_error("mmap file name empty");
  if (strlen(filename) >= MAX_IDENT_LEN)
    P2_runtime_error("mmap file name \"%s\" too long", filename);

  /* Is file already opened? If so, we can return after checking to
     make sure that the file has valid properties. */
  assert(mmap_file_open[f] == TRUE || mmap_file_open[f] == FALSE);
  if (mmap_file_open[f])
  {
    /* File already opened. */
    assert(MMAP_FD_VALID(mmap_fd[f]));
    /* Make sure file is open. */
    if (fstat(mmap_fd[f], &fstat_buf) < 0)
      P2_runtime_perror("Can not find open mmap file");
    /* Make sure file has the correct size. */
    if (fstat_buf.st_size != total_size)
      P2_runtime_error("Existing mmap file \"%s\" size mismatch", filename);
    /* Make sure file has the correct name. */
    if (strcmp(filename, (mmap_header[f])->filename) != 0)
       P2_runtime_error("Filenames \"%s\" and \"%s\" both hash to %d",
                        (mmap_header[f])->filename, filename, f);
    /* Make sure magic pattern is correct. */
    if ((mmap_header[f])->magic_pattern != MAGIC_PATTERN)
      P2_runtime_error("P2_open_mmap_memory: Magic pattern mis-match:"
                       " file \"%s\" corrupted?", filename);
    /* Return file descriptor. */
    return(mmap_fd[f]);
  }

  /* Create file with given filename, allow reading and writing.
     If file already exists, that's okay.  If file is not persistent,
     truncate its length to zero. */
  mmap_fd[f] = open(filename,
    (persistent)? O_RDWR|O_CREAT : O_RDWR|O_CREAT|O_TRUNC, 0666);
  if (mmap_fd[f] < 0)
    P2_runtime_perror("Can not open mmap file \"%s\"", filename);

  /* See if the file has been initialized.
     We'll know if its first 4 bytes equal the magic pattern. */
  i = read(mmap_fd[f], &file_header, sizeof(file_header));
  if (i < 0)
    P2_runtime_perror("Can not read mmap file \"%s\"", filename);
  
  /* Either initialize the file, or simply mmap it. */
  if (!persistent
      || (i != sizeof(file_header)
          || file_header.magic_pattern != MAGIC_PATTERN))
  {
    /*** The file has not been initialized: initialize it. ***/

    /* Make sure that the file is large enough for an mmap. */
    if (lseek(mmap_fd[f], total_size-1, SEEK_SET) < 1)
      P2_runtime_perror("Can not find end of mmap file \"%s\"", filename);
    if (write(mmap_fd[f], "1", 1) < 1)
      P2_runtime_perror("File \"%s\" too small for mmap", filename);
    if (lseek(mmap_fd[f], 0, SEEK_SET))
      P2_runtime_perror("Can not find beginning of mmap file \"%s\"", filename);

#ifdef MAP_VARIABLE
    /* MAP_VARIABLE places region at implementation-computed address.
       It is defined on HP-UX, but not SunOS or Solaris. (JAT) */
    base = mmap(0, total_size, PROT_READ|PROT_WRITE,
                MAP_VARIABLE|MAP_SHARED, mmap_fd[f], 0);
#else
    base = mmap(0, total_size, PROT_READ|PROT_WRITE, 
                MAP_SHARED, mmap_fd[f], 0);
#endif
#if defined(MAP_FAILED)
    /* If MAP_FAILED is defined, use it. */
    if (base == MAP_FAILED)
#else
    /* Otherwise, assume MAP_FAILED is -1. */
    if (base == (void *) -1)
#endif
      P2_runtime_perror("mmap() failed: can not map memory file \"%s\"",
                        filename);

    /* Make sure that the mmap region that we just created does not
       overlap any existing mmap region. */
    assert_mmap_region_valid(base, total_size, filename, f);

    (mmap_header[f])                 = (MMAP_HEADER *) base;
    (mmap_header[f])->magic_pattern  = MAGIC_PATTERN;
    (mmap_header[f])->size           = total_size;
    (mmap_header[f])->base           = base;
    (mmap_header[f])->free           = base + header_size;
    strcpy((mmap_header[f])->filename, filename);

    /* Replace this with a memset()??? (JAT) */
    for (i = 0; i < MAX_MMAP_VAR; i++)
    {
      (mmap_header[f])->v[i].in_use  = FALSE;
#ifndef NDEBUG
      (mmap_header[f])->v[i].p       = NULL;
      (mmap_header[f])->v[i].name[0] = '\0';
#endif
    }
  }

  else
  {
    /*** The file has been initialized: simply mmap it. ***/

    /* Make sure that the mmap region that we are going to create will
       not overlap any existing mmap region. */
    assert_mmap_region_valid(file_header.base, file_header.size, filename, f);

    base = mmap(file_header.base, file_header.size,
                PROT_READ|PROT_WRITE,
                MAP_FIXED|MAP_SHARED, mmap_fd[f], 0);
#if defined(MAP_FAILED)
    /* If MAP_FAILED is defined, use it. */
    if (base == MAP_FAILED)
#else
    /* Otherwise, assume MAP_FAILED is -1. */
    if (base == (void *) -1)
#endif
      P2_runtime_perror("mmap() failed: can not re-mmap memory file \"%s\"",
                        filename);

    /* Make sure file has been re-mapped to the same address that it
       was originally mapped to. */
    if (base != file_header.base)
      P2_runtime_error("re-mmap memory file \"%s\" address mismatch",
                        filename);
    /* Make sure the mmap header is valid. */
    (mmap_header[f]) = (MMAP_HEADER *) base;
    if ((mmap_header[f])->magic_pattern != MAGIC_PATTERN)
      P2_runtime_error("re-mmap memory file \"%s\" does not contain"
                       " MAGIC_PATTERN", filename);
    if ((mmap_header[f])->size != total_size)
      P2_runtime_error("re-mmap memory file \"%s\" size mismatch", filename);
    if (strcmp((mmap_header[f])->filename, filename) != 0)
      P2_runtime_error("re-mmap memory file name mismatch for \"%s\""
                       " and \"%s\"", filename, (mmap_header[f])->filename);
    assert(MMAP_ADDRESS_VALID((mmap_header[f])->free, f));
  }

  /* Remember that we've opened the file. */
  mmap_file_open[f] = TRUE;

  /* Return file descriptor. */
  return(mmap_fd[f]);
}

/*****************************************************************************/
/*                  Close memory.                                            */
/*****************************************************************************/

/* Unmap the file and close it. */

void
P2_close_mmap_memory (int persistent, int f)
{
  assert(f >= 0 && f < MAX_MMAP_FILE);
  assert(persistent == 0 || persistent == 1);
  assert(mmap_file_open[f] == TRUE || mmap_file_open[f] == FALSE);

  if (mmap_file_open[f])
  {
    char filename[MAX_IDENT_LEN];
    /* Create a temporary copy of file name since we need the file
       name for error reporting, but is currently stored only in the
       mmap header, which (if the file is not persistent) will go away
       when we un-map the file. */
    strcpy(filename, (mmap_header[f])->filename);
    /* Make sure magic pattern is correct. */
    if ((mmap_header[f])->magic_pattern != MAGIC_PATTERN)
      P2_runtime_error("P2_close_mmap_memory: Magic pattern mis-match:"
                       " file \"%s\" corrupted?", filename);
    /* Un-map file. */
    if (munmap((mmap_header[f])->base, (mmap_header[f])->size) == -1)
       P2_runtime_perror("munmap() failed: can not un-map memory file \"%s\"",
                         filename);
    /* Close file. */
    if (close(mmap_fd[f]) < 0)
      P2_runtime_perror("Can not close mmap file \"%s\"", filename);
    /* If not persistent, delete file. */
    if (!persistent)
      if (unlink(filename) < 0)
        P2_runtime_perror("Can not delete mmap file \"%s\"", filename);
    /* Remember that we've closed the file. */
    mmap_file_open[f] = FALSE;
  }
}

/*****************************************************************************/
/*                  Synchronize memory.                                      */
/*****************************************************************************/

void
P2_sync_mmap_memory (const void *addr, int len, int async, int f)
{
  assert(async == 0 || async == 1);
  assert(f >= 0 && f < MAX_MMAP_FILE);
  if (msync(mmap_header[f]->base, mmap_header[f]->size,
            (async)? MS_ASYNC : MS_SYNC) < 0)
    P2_runtime_perror("Can not msync mmap file with memory");
}

/*****************************************************************************/
/*                  Variables.                                               */
/*****************************************************************************/

/* Allocate a new mmap variable with the given name and size, and
   return it's address. */

static void *
new_mmap_var (const char *name, int size_in_bytes, int f)
{
  MMAP_VAR *v;
  
  assert(f >= 0 && f < MAX_MMAP_FILE);
  assert((mmap_header[f])->magic_pattern == MAGIC_PATTERN);
  assert(name != NULL);
  assert(MMAP_VAR_NAME_VALID(name));
  assert(size_in_bytes >= 0);
   assert(size_in_bytes < (mmap_header[f])->size); 

  /* Check to see if the new allocation will fill-up mmap memory. */
  if (MMAP_ADDRESS_HIGH((mmap_header[f])->free + size_in_bytes, f))
    P2_runtime_error("out of mmap memory: mmap memory full");

  /* Look for an unused mmap variable. */
  for (v = &(mmap_header[f])->v[0];
       v < &(mmap_header[f])->v[MAX_MMAP_VAR] && v->in_use;
       v++)
  {
#ifndef NDEBUG
    assert(MMAP_ADDRESS_VALID(v, f));
    assert(v->in_use == TRUE || v->in_use == FALSE);
    assert(MMAP_ADDRESS_VALID(v->p, f));
    assert(MMAP_VAR_NAME_VALID(v->name));
#endif
  }
  if (v == &(mmap_header[f])->v[MAX_MMAP_VAR])
    P2_runtime_error("too many mmap variables declared");

  /* Fill-in fields of mmap variable structure. */
  v->in_use = TRUE;
  v->p = (mmap_header[f])->free;
  strcpy(v->name, name);

  /* Update free pointer. */
  (mmap_header[f])->free = (mmap_header[f])->free + size_in_bytes;

  /* Return mmap variable. */
  return(v->p);
}

/* If an old mmap variable with the given name exists, return it's address.
   Otherwise, return NULL. */

static void *
old_mmap_var (const char *name, int f)
{
  MMAP_VAR *v; 
  
  assert(f >= 0 && f < MAX_MMAP_FILE);
  assert((mmap_header[f])->magic_pattern == MAGIC_PATTERN);
  assert(name != NULL);
  assert(MMAP_VAR_NAME_VALID(name));

  /* Look for the mmap variable. */
  for (v = &(mmap_header[f])->v[0];
       v < &(mmap_header[f])->v[MAX_MMAP_VAR];
       v++)
  {
#ifndef NDEBUG
    assert(MMAP_ADDRESS_VALID(v, f));
    assert(v->in_use == TRUE || v->in_use == FALSE);
#endif
    if (v->in_use && (strcmp(v->name, name) == 0))
      /* Found: return mmap variable. */
      return(v->p);
  }

  /* Not found: return NULL. */
  return(NULL);
}

/* Delete mmap variable with given name.
   If name does not exist, no error is returned. */
/* Why is the formal parameter called "varname" rather than "name"??? (JAT) */

void
delete_mmap_var (const char *varname, int f)
{
  MMAP_VAR *v;
  
  assert(f >= 0 && f < MAX_MMAP_FILE);
  assert((mmap_header[f])->magic_pattern == MAGIC_PATTERN);
  assert(varname != NULL);
  assert(MMAP_VAR_NAME_VALID(varname));

  /* Look for the mmap variable. */
  for (v = &(mmap_header[f])->v[0];
       v < &(mmap_header[f])->v[MAX_MMAP_VAR];
       v++)
  {
#ifndef NDEBUG
    assert(MMAP_ADDRESS_VALID(v, f));
    if (v->in_use) {
      assert(v->in_use == FALSE);
      assert(v->p == NULL);
      assert(v->name[0] == '\0');
    }
    else {
      assert(v->in_use == TRUE);
      assert(MMAP_ADDRESS_VALID(v->p, f));
      assert(MMAP_VAR_NAME_VALID(v->name));
    }
#endif
    if (strcmp(v->name, varname) == 0)
    {
      /* Found: break */
      v->in_use = FALSE;
#ifndef NDEBUG
      v->p = NULL;
      v->name[0] = '\0';
#endif
      break;
    }
  }

  return;
}

/*  Return address of mmap variable.
    Create variable if not already present. */

void *
P2_open_mmap_var (const char *varname, int size_in_bytes, BOOLEAN *new, int f)
{
  MMAP_VAR *v;
  
  assert(f >= 0 && f < MAX_MMAP_FILE);
  assert((mmap_header[f])->magic_pattern == MAGIC_PATTERN);
  assert(varname != NULL);
  assert(MMAP_VAR_NAME_VALID(varname));
  assert(size_in_bytes >= 0);
   assert(size_in_bytes < (mmap_header[f])->size); 

  v = old_mmap_var(varname, f);
  if (v == NULL)
  {
    (*new) = TRUE;
    v = new_mmap_var(varname, size_in_bytes, f);
  }
  else
    (*new) = FALSE;

  assert(MMAP_ADDRESS_VALID(v, f));
  return(v);
}

/*****************************************************************************/
/*                  Allocate and free.                                       */
/*****************************************************************************/

/* Return the address of an mmap segment having size size_in_bytes. */

void *
P2_mmap_alloc (int size_in_bytes, int f)
{
  void *v;
  
  assert(f >= 0 && f < MAX_MMAP_FILE);
  assert((mmap_header[f])->magic_pattern == MAGIC_PATTERN);
  assert(size_in_bytes >= 0);
  assert(size_in_bytes < (mmap_header[f])->size);
  assert(MMAP_ADDRESS_VALID((mmap_header[f])->free, f));

  /* Check to see if the new allocation will fill-up mmap memory. */
  if (MMAP_ADDRESS_HIGH((mmap_header[f])->free + size_in_bytes, f))
    P2_runtime_error("out of mmap memory: mmap memory full");

#if 0
  P2_trace("(mmap_header[f]) = %x", (mmap_header[f]));
  P2_trace("(mmap_header[f])->base = %x", (mmap_header[f])->base);
  P2_trace("(mmap_header[f])->free = %x", (mmap_header[f])->free);
  P2_trace("(mmap_header[f])->filename = \"%s\"", (mmap_header[f])->filename);
#endif

  /* Allocate memory. */
  v = (mmap_header[f])->free;

  /* Update free pointer. */
  (mmap_header[f])->free = v + size_in_bytes;

  return(v);
}

/* Currently, do nothing. */

void
P2_mmap_free (const void *v, int f)
{
  assert(f >= 0 && f < MAX_MMAP_FILE);
  assert((mmap_header[f])->magic_pattern == MAGIC_PATTERN);
  assert(MMAP_ADDRESS_VALID(v, f));
}

/*****************************************************************************/
/*                  Overflow.                                                */
/*****************************************************************************/

BOOLEAN
P2_mmap_overflow (int f)
{
  return(MMAP_ADDRESS_HIGH((mmap_header[f])->free, f));
}

BOOLEAN
P2_mmap_varoverflow (int size_in_bytes, int f)
{
  return(MMAP_ADDRESS_HIGH((mmap_header[f])->free + size_in_bytes, f));
}
