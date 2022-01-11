#include "decode.h"
#include "main.h"

void decode_int_to_array (int input, int *result) {
  int i = 0;
  while (input != 0) {
    int count = 0;
    while (!(input & 1)) {
      count++;
      input >>= 1;
    }
    input >>= 1;
    result[i] = count;
    i++;
  }
  result[i] = -1;
}

struct pair decode_int_to_pair1 (int input) {
  int count = 0;
  while (input & 1) {
    count++; input >>= 1;
  }
  input >>= 1;
  return (struct pair) {count, input};
}

struct pair decode_int_to_pair2 (int input) {
  int count = 0;
  while (!(input & 1)) {
    count++;
    input >>= 1;
  }
  input >>= 1;
  return (struct pair) {count, input};
}

struct body decode_int_to_body (int input) {
  struct body res = {HALT, 0, 0, 0};

  if (input == 0) return res;

  struct pair pair = decode_int_to_pair2 (input);
  if (pair.first % 2 == 0) {
    res.type   = ADD;
    res.reg    = pair.first / 2;

    res.label1 = pair.second;
  } else {
    res.type          = SUBTRACT;
    res.reg           = (pair.first - 1) / 2;

    struct pair pair2 = decode_int_to_pair1 (pair.second);
    res.label1        = pair2.first;
    res.label2        = pair2.second;
  }

  return res;
}
