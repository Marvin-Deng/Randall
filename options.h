#ifndef OPTIONS_H
#define OPTIONS_H

enum Input
{
    NONE,
    RDRAND,
    LDRAND,
    SLASH_F
};
enum Ouput
{
    STDIO,
    N
};

struct options
{
    bool isvalid;
    long long nbytes;
    enum Input input;
    char *file;
    enum Ouput output;
    unsigned int block_size;
};

void readoptions(int argc, char **argv, struct options *opts);

#endif
