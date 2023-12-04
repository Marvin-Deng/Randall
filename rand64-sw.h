#ifndef RAND64_SW_H
#define RAND64_SW_H

#include <stdio.h>

void initfile(char *file);

void software_rand64_init(void);

unsigned long long software_rand64(void);

void software_rand64_fini(void);

void software_lrand48_init(void);

unsigned long long software_lrand48(void);

void software_lrand48_fini(void);

#endif
