#ifndef PRETTY_PRINT_H
#define PRETTY_PRINT_H

#include "common.h"

void print_bits          (int size, void *ptr);
void print_body          (struct body body);
int  print_configuration (int *configuration);

#endif
