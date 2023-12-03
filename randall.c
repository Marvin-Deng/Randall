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
#include <unistd.h>

#include "options.h"
#include "rand64-hw.h"
#include "rand64-sw.h"
#include "output.h"

/* Main program, which outputs N bytes of random data.  */
int main(int argc, char **argv)
{
  struct options opts;
  opts.input = NONE;
  opts.output = STDIO;

  readoptions(argc, argv, &opts);
  long long nbytes = opts.nbytes;

  // Check if the input is valid
  if (!opts.isvalid)
  {
    fprintf(stderr, "Error: Invalid input");
    return 1;
  }

  if (nbytes == 0)
  {
    return 0;
  }

  void (*initialize)(void);
  unsigned long long (*rand64)(void);
  void (*finalize)(void);

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
      fprintf(stderr, "Error: rdrand is not available\n");
      return 1;
    }
  }
  else if (opts.input == LRAND)
  {
    initialize = hardware_rand64_init;
    rand64 = software_lrand48;
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
    fprintf(stderr, "Error: Invalid input format");
    return 1;
  }

  initialize();
  int wordsize = sizeof rand64();
  int output_errno = 0;

  if (opts.output == STDIO)
  {
    while (0 < nbytes)
    {
      unsigned long long x = rand64();
      int outbytes = nbytes < wordsize ? nbytes : wordsize;
      if (!writebytes(x, outbytes))
      {
        output_errno = errno;
        break;
      }
      nbytes -= outbytes;
    }

    if (fclose(stdout) != 0)
      output_errno = errno;

    if (output_errno)
    {
      errno = output_errno;
      perror("output");
    }
  }
  else if (opts.output == N)
  {
    if (opts.block_size == 0)
    {
      fprintf(stderr, "Error: Block size cannot be 0 \n");
      return 1;
    }
    unsigned int block = opts.block_size * 2;
    char *buffer = malloc(block);
    if (buffer == NULL)
    {
      fprintf(stderr, "Error: Buffer cannot be NULL \n");
      return 1;
    }
    while (0 < nbytes)
    {
      int curr_block = nbytes < block ? nbytes : block;
      unsigned long long x;
      for (int i = 0; i < curr_block; i += sizeof(x))
      {
        x = rand64();
        for (size_t j = 0; j < sizeof(x); j++)
        {
          unsigned char byte = *((unsigned char *)&x + j);
          buffer[i + j] = byte;
        }
      }
      write(1, buffer, curr_block);
      nbytes -= curr_block;
    }
    free(buffer);
  }

  finalize();
  return !!output_errno;
}
