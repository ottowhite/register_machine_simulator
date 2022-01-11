#ifndef ENCODE_H
#define ENCODE_H

#include "common.h"

int encode_pair_to_int1 (struct pair pair);
int encode_pair_to_int2 (struct pair pair);
int encode_body_to_int  (struct body body);
int encode_array_to_int (int *arr);

#endif
