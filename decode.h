#ifndef DECODE_H
#define DECODE_H

#include "common.h"

void        decode_int_to_array (int input, int *result);
struct pair decode_int_to_pair1 (int input);
struct pair decode_int_to_pair2 (int input);
struct body decode_int_to_body (int input);

#endif
