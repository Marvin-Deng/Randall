#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h>
#include <errno.h>

#include "output.h"

bool write_bytes(unsigned long long x, int nbytes)
{
    do
    {
        if (putchar(x) < 0)
            return false;
        x >>= CHAR_BIT;
        nbytes--;
    } while (0 < nbytes);

    return true;
}

int write_output(long long nbytes, int output, int block_size, unsigned long long rand64()) {
    
  int wordsize = sizeof rand64();
  int output_errno = 0;

  if (output == 0)
  {
    while (0 < nbytes)
    {
      unsigned long long x = rand64();
      int outbytes = nbytes < wordsize ? nbytes : wordsize;
      if (!write_bytes(x, outbytes))
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
  else if (output == 1)
  {
    unsigned int block = block_size * sizeof(char);
    char *buffer = malloc(block);
    if (buffer == NULL)
    {
      fprintf(stderr, "Error: Buffer cannot be NULL\n");
      exit(1);
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

  return output_errno;
}