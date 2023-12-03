#ifndef OPTIONS_H
#define OPTIONS_H

enum Input { NONE, RDRAND, LRAND, SLASH_F };

struct options {
    bool isvalid;
    long long nbytes;
    enum Input input;
};

void readoptions(int argc, char **argv, struct options *opts);

#endif 
