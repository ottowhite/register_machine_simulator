#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>

#include "main.h"

static int *       decode_int_to_array (int input);
static struct pair decode_int_to_pair1 (int input);
static struct pair decode_int_to_pair2 (int input);

static int encode_pair_to_int1 (struct pair pair);
static int encode_pair_to_int2 (struct pair pair);
static int encode_body_to_int  (struct body body);
static int encode_array_to_int (int *arr);

static void execute_program (int *configuration, struct body *program);

static void print_bits          (size_t const size, void const * const ptr);
static void print_body          (struct body body);
static int  print_configuration (int *configuration);

static void print_bits(size_t const size, void const * const ptr) {
    unsigned char *b = (unsigned char*) ptr;
    unsigned char byte;
    int i, j;
    
		printf ("(");
    for (i = size-1; i >= 0; i--) {
        for (j = 7; j >= 0; j--) {
            byte = (b[i] >> j) & 1;
            printf("%u", byte);
        }
    }
		printf (")");
}

static int *decode_int_to_array (int input) {
  int *res = calloc (100, sizeof (int));

  int i = 0;
  while (input != 0) {
    int count = 0;
    while (!(input & 1)) {
      count++;
      input >>= 1;
    }
    input >>= 1;
    res[i] = count;
    i++;
  }
  res[i] = -1;
  
  return res;
}

static struct pair decode_int_to_pair1 (int input) {
  int count = 0;
  while (input & 1) {
    count++; input >>= 1;
  }
  input >>= 1;
  return (struct pair) {count, input};
}

static struct pair decode_int_to_pair2 (int input) {
  int count = 0;
  while (!(input & 1)) {
    count++;
    input >>= 1;
  }
  input >>= 1;
  return (struct pair) {count, input};
}

static int encode_pair_to_int1 (struct pair pair) {
  return (int) (pow (2, pair.first) * (2 * (pair.second) + 1)) - 1;
}

static int encode_pair_to_int2 (struct pair pair) {
  return (int) pow (2, pair.first) * (2 * (pair.second) + 1);
}

static struct body decode_int_to_body (int input) {
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

static int encode_body_to_int (struct body body) {
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

static int encode_array_to_int (int *arr) {
  int list = 0;

  int i = 0;
  for (i = 0; arr[i] != -1; i++);

  for (i--; i >= 0; i--) {
    list = encode_pair_to_int2 (
        (struct pair) {arr[i], list});
  }

  return list;
}

static void print_body (struct body body) {
  switch (body.type) {
    case HALT:      printf ("HALT\n"); break;
    case ADD:       printf ("R%d+ -> L%d\n", body.reg, body.label1); break;
    case SUBTRACT:  printf ("R%d- -> L%d,L%d\n", body.reg, body.label1, 
                        body.label2); break;
  }
}

static int print_configuration (int *configuration) {
  printf ("L:\t%d\n", configuration[0]);
  for (int i = 1; configuration[i] != -1; i++) {
    printf ("R%d:\t%d\n", i, configuration[i]);
  }
}

static void execute_program (int *configuration, struct body *program) {
  print_configuration (configuration);
  int label        = configuration[0];
  struct body body = program[label];

  if (body.type == HALT) {
    return;
  }

  if (body.type == ADD) {
    
    configuration[body.reg + 1]++;
    configuration[0] = body.label1;

  } else if (body.type == SUBTRACT) {
    if (configuration[body.reg + 1] > 0) {

      configuration[body.reg + 1]--;
      configuration[0] = body.label1;

    } else {

      configuration[0] = body.label2;

    }

  }
  execute_program (configuration, program);
}

int main (void) {
	int input = 20483;
  int *res = decode_int_to_array (input);

  assert(encode_array_to_int (decode_int_to_array (input)) == input);

  printf ("Decoded program: \n");
  res[0] = 46;
  for (int i = 0; res[i] != -1; i++) {
    printf ("L%d: ", i);
    print_body (decode_int_to_body(res[i]));
  }
  
  struct body program[20];
  program[0] = (struct body) { SUBTRACT,  1,  2,  1 };
  program[1] = (struct body) { HALT                 };
  program[2] = (struct body) { SUBTRACT,  1,  3,  4 };
  program[3] = (struct body) { SUBTRACT,  1,  5,  4 };
  program[4] = (struct body) { HALT                 };
  program[5] = (struct body) { ADD,       0,  0     };

  int configuration[4] = {0, 0, 7, -1};

  int encoded_program_arr[20];
  encoded_program_arr[0] = encode_body_to_int (program[0]);  
  encoded_program_arr[1] = encode_body_to_int (program[1]);
  encoded_program_arr[2] = encode_body_to_int (program[2]);
  encoded_program_arr[3] = encode_body_to_int (program[3]);
  encoded_program_arr[4] = encode_body_to_int (program[4]);
  encoded_program_arr[5] = encode_body_to_int (program[5]);
  encoded_program_arr[6] = -1;

  printf ("\nProgram from encoded array, decoded\n");
  for (int i = 0; encoded_program_arr[i] != -1; i++) {
    printf ("L%d: ", i);
    print_body (decode_int_to_body(encoded_program_arr[i]));
  }

  printf ("\n\n");

  // execute_program (configuration, program);

  free (res);
  return 0;
}
