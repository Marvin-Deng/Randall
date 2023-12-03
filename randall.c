/* Generate N bytes of random output.  */

/* When generating output this program uses the x86-64 RDRAND
   instruction if available to generate random numbers, falling back
   on /dev/random and stdio otherwise.

   This program is not portable.  Compile it with gcc -mrdrnd for a
   x86-64 machine.

   Copyright 2015, 2017, 2020 Paul Eggert

   This program is free software: you can redistribute it and/or
   modify it under the terms of the GNU General Public License as
   published by the Free Software Foundation, either version 3 of the
   License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

#include <cpuid.h>
#include <errno.h>
#include <immintrin.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "options.h"
#include "rand64-hw.h"
#include "rand64-sw.h"
#include "output.h"

/* Main program, which outputs N bytes of random data.  */
int main (int argc, char **argv)
{
  struct options opts;
  readoptions(argc, argv, &opts);
  long long nbytes = opts.nbytes;

  // Check if the input is valid
  if (!opts.isvalid)
  {
    fprintf(stderr, "%s: usage: %s NBYTES\n", argv[0], argv[0]);
    return 1;
  }

  if (nbytes == 0)
  {
    return 0;
  }

  /* Now that we know we have work to do, arrange to use the
     appropriate library.  */
  void (*initialize) (void);
  unsigned long long (*rand64) (void);
  void (*finalize) (void);

  if (opts.input == NONE)
  {
    initialize = software_rand64_init;
    rand64 = software_rand64;
    finalize = software_rand64_fini;
  }
  else if (opts.input == RDRAND)
  {
    if (rdrand_supported())
    {
      initialize = hardware_rand64_init;
      rand64 = hardware_rand64;
      finalize = hardware_rand64_fini;
    }
    else
    {
      fprintf(stderr, "rdrand is not available\n");
      return 1;
    }
  }
  else if (opts.input == LRAND)
  {
    initialize = hardware_rand64_init;
    rand64 = hardware_lrand48;
    finalize = hardware_rand64_fini;
  }
  else if (opts.input == SLASH_F)
  {
    initfile(opts.file);
    initialize = software_rand64_init;
    rand64 = software_rand64;
    finalize = software_rand64_fini;
  }
  else
  {
    fprintf(stderr, "Input invalid\n");
    return 1;
  }

  initialize ();
  int wordsize = sizeof rand64 ();
  int output_errno = 0;

  do
    {
      unsigned long long x = rand64 ();
      int outbytes = nbytes < wordsize ? nbytes : wordsize;
      if (!writebytes (x, outbytes))
	{
	  output_errno = errno;
	  break;
	}
      nbytes -= outbytes;
    }
  while (0 < nbytes);

  if (fclose (stdout) != 0)
    output_errno = errno;

  if (output_errno)
    {
      errno = output_errno;
      perror ("output");
    }

  finalize ();
  return !!output_errno;
}
