#include <math.h>

#include "encode.h"
#include "common.h"

int encode_pair_to_int1 (struct pair pair) {
  return (int) (pow (2, pair.first) * (2 * (pair.second) + 1)) - 1;
}

int encode_pair_to_int2 (struct pair pair) {
  return (int) pow (2, pair.first) * (2 * (pair.second) + 1);
}

int encode_body_to_int (struct body body) {
  if (body.type == HALT) return 0;
  if (body.type == ADD) {
    return encode_pair_to_int2 ((struct pair) {2 * body.reg, body.label1});
  } else if (body.type == SUBTRACT) {
    return encode_pair_to_int2 (
        (struct pair) {2 * body.reg + 1,
                       encode_pair_to_int1 ((struct pair) {body.label1, 
                                                           body.label2})});
  }
}

int encode_array_to_int (int *arr) {
  int list = 0;

  int i = 0;
  for (i = 0; arr[i] != -1; i++);

  for (i--; i >= 0; i--) {
    list = encode_pair_to_int2 (
        (struct pair) {arr[i], list});
  }

  return list;
}
