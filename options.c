#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

#include "options.h"

static bool isPosNumber(char *string)
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
            else
            {
                fprintf(stderr, "Error: Invalid input format. Expected rdrand, ldrand48_r, or a file path as arguments\n");
                exit(1);
            }
            opts->isvalid = true;
            break;

        case 'o':

            if (isPosNumber(optarg))
            {
                opts->output = N;
                int block_size = atoi(optarg);
                if (block_size == 0)
                {
                    fprintf(stderr, "Error: Block size cannot be 0\n");
                    exit(1);
                }
                opts->block_size = block_size;
            }
            else if (strcmp("stdio", optarg) == 0)
            {
                opts->output = STDIO;
            }
            else
            {
                fprintf(stderr, "Error: Invalid output format. Expected a positve integer or stdio as arguments\n");
                exit(1);
            }
            opts->isvalid = true;
            break;
        
        case ':':
            fprintf (stderr, "Error: Option -%c requires an operand\n", optopt);
            exit(1);

        case '?':
            fprintf (stderr, "Error: Invalid option: '-%c'\n", optopt);
            exit(1);
        }
    }

    // Input finsihed parsing without reaching an nbytes value
    if (optind >= argc)
    {
        fprintf(stderr, "Error: Insufficient command-line arguments. Please include the required 'nbytes' value.\n");
        exit(1);
    }

    // Gets the number of bytes at then end of the input
    opts->nbytes = atol(argv[optind]);
    if (opts->nbytes >= 0)
    {
        opts->isvalid = true;
    }
}