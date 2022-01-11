#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>

#include "common.h"
#include "encode.h"
#include "decode.h"
#include "execute.h"
#include "pretty_print.h"

static void demonstrate_execution(void);
static void demonstrate_translation(int input);
static void print_usage(void);

int main(int argc, char **argv) {
  if (argc > 1) {
    if (!strcmp(argv[1], "-g") && argc == 3) {
      /* Godel number to RM translation case */
      demonstrate_translation(atoi(argv[2]));
    } else if (!strcmp(argv[1], "-d") && argc == 2) {
      /* Demonstration */
      demonstrate_execution();
    } else {
      /* Invalid argument */
      print_usage();
    }

  } else {
    /* Invalid number of arguments */
    print_usage();
  }
  return 0;
}

static void demonstrate_translation(int input) {
  int result[100];
  printf("The Godel number %d can be uniquely translated to the register machine: \n\n", input);
  decode_int_to_array (input, result);

  for (int i = 0; result[i] != -1; i++) {
    printf ("L%d: ", i);
    print_body (decode_int_to_body(result[i]));
  }

}

static void demonstrate_execution(void) {
  /* RM program execution. */
  int configuration[4] = {0, 0, 7, -1};

  struct body program[20] = {
    (struct body) { SUBTRACT,  1,  2,  1 },
    (struct body) { HALT                 },
    (struct body) { SUBTRACT,  1,  3,  4 },
    (struct body) { SUBTRACT,  1,  5,  4 },
    (struct body) { HALT                 },
    (struct body) { ADD,       0,  0     }
  };

  int encoded_program_arr[20] = {
    encode_body_to_int (program[0]),
    encode_body_to_int (program[1]),
    encode_body_to_int (program[2]),
    encode_body_to_int (program[3]),
    encode_body_to_int (program[4]),
    encode_body_to_int (program[5]),
    -1
  };

  printf ("Program from encoded array, decoded\n");
  for (int i = 0; encoded_program_arr[i] != -1; i++) {
    printf ("L%d: ", i);
    print_body (decode_int_to_body(encoded_program_arr[i]));
  }
  printf("\n");

  execute_program (configuration, program);
}

static void print_usage(void) {
  printf(
      "Usage: ./main OPTION [ARGS..]\n\n"
      "   -g: Translate a given godel number into a register machine. \n"
      "   -d: Perform an execution trace on a hard coded register machine. \n");
}
