#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <cpuid.h>
#include <string.h>
#include <ctype.h>

#include "options.h"

bool isNumber(char *string)
{
    if (*string == '\0')
    {
        return false;
    }

    for (int i = 0; string[i] != '\0'; i++)
    {
        if (!isdigit((unsigned char)string[i]))
        {
            return false;
        }
    }
    return true;
}

void readoptions(int argc, char **argv, struct options *opts)
{
    opts->isvalid = false;

    // Parse options
    int c;
    while ((c = getopt(argc, argv, ":i:o:")) != -1)
    {
        switch (c)
        {

        case 'i':
            if (strcmp("rdrand", optarg) == 0)
            {
                opts->input = RDRAND;
            }
            else if (strcmp("ldrand48_r", optarg) == 0)
            {
                opts->input = LRAND;
            }
            else if ('/' == optarg[0])
            {
                opts->input = SLASH_F;
                opts->file = optarg;
            }
            opts->isvalid = true;
            break;

        case 'o':
            if (isNumber(optarg))
            {
                opts->output = N;
                opts->block_size = atoi(optarg);
            }
            else if (strcmp("stdio", optarg) == 0)
            {
                opts->output = STDIO;
            }
            else
            {
                fprintf(stderr, "Invalid output format");
                exit(1);
            }
            opts->isvalid = true;
            break;
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