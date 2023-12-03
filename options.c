#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <cpuid.h>
#include <string.h>

#include "options.h"

void readoptions(int argc, char **argv, struct options *opts)
{
    opts->isvalid = false;

    // Parse options
    int c;
    while ((c = getopt(argc, argv, ":i:o:")) != -1)
    {
        switch (c)
        {

        case 'i': // Option -i for input
            if (strcmp("rdrand", optarg) == 0)
            {
                opts->input = RDRAND;
            }
        }
    }

    // Finished parsing line
    if (optind >= argc)
    {
        return;
    }

    // Gets the number of bytes at then end of the input
    opts->nbytes = atol(argv[optind]);
    if (opts->nbytes >= 0)
    {
        opts->isvalid = true;
    }
}