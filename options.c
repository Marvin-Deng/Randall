#include "options.h"
#include <cpuid.h>
#include <errno.h>
#include <immintrin.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

long long checkoptions(int argc, char **argv) {
    /* Check arguments.  */
  bool valid = false;
  long long nbytes;
  if (argc == 2) {
      char *endptr;
      errno = 0;
      nbytes = strtoll (argv[1], &endptr, 10);
      if (errno)
	    perror (argv[1]);
      else
	valid = !*endptr && 0 <= nbytes;
    }
  if (!valid)
    {
      fprintf (stderr, "%s: usage: %s NBYTES\n", argv[0], argv[0]);
      exit(1);
    }
    /* If there's no work to do, don't worry about which library to use.  */
  if (nbytes == 0)
    exit(0);
    return nbytes;
}