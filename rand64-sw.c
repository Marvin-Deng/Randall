#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "rand64-sw.h"

static struct drand48_data drand_data;

/* Input stream containing random bytes.  */
static FILE *urandstream;

/* Initialize the software implementation on a file  */
void initfile(char *file)
{
  urandstream = fopen(file, "r");
  if (!urandstream)
  {
    fprintf(stderr, "Error: Invalid file path: %s\n", file);
    exit(1);
  }
}

/* Initialize the software rand64 implementation.  */
void software_rand64_init(void)
{
  if (urandstream == NULL)
    initfile("/dev/random");
}

/* Return a random value, using software operations.  */
unsigned long long software_rand64(void)
{
  unsigned long long int x;
  if (fread(&x, sizeof x, 1, urandstream) != 1)
    abort();
  return x;
}

/* Finalize the software rand64 implementation.  */
void software_rand64_fini(void)
{
  fclose(urandstream);
}

/* Initialize the software ldrand48 implementation.  */
void software_lrand48_init(void)
{
  srand48_r(time(NULL), &drand_data);
}

/* Return a random value, using ldrand48_r().  */
unsigned long long software_lrand48(void)
{
  long int result;
  lrand48_r(&drand_data, &result);
  return (unsigned long long)result;
}

/* Finalize the software ldrand48_r() implementation.  */
void software_lrand48_fini(void)
{
}
