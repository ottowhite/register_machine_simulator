#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>

#include "common.h"
#include "encode.h"
#include "decode.h"
#include "execute.h"
#include "pretty_print.h"

int main (void) {
  /* Godel number to RM program translation. */
	int input = 20483;
  int result[100];
  decode_int_to_array (input, result);

  assert(encode_array_to_int (result) == input);

  printf ("Decoded program: \n");
  result[0] = 46;
  for (int i = 0; result[i] != -1; i++) {
    printf ("L%d: ", i);
    print_body (decode_int_to_body(result[i]));
  }
  
  /* RM program execution. */
  int configuration[4] = {0, 0, 7, -1};

  struct body program[20];
  program[0] = (struct body) { SUBTRACT,  1,  2,  1 };
  program[1] = (struct body) { HALT                 };
  program[2] = (struct body) { SUBTRACT,  1,  3,  4 };
  program[3] = (struct body) { SUBTRACT,  1,  5,  4 };
  program[4] = (struct body) { HALT                 };
  program[5] = (struct body) { ADD,       0,  0     };

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

  execute_program (configuration, program);
  return 0;
}
