#include <stdio.h>

#include "pretty_print.h"
#include "common.h"

void print_body (struct body body) {
  switch (body.type) {
    case HALT:      printf ("HALT\n"); break;
    case ADD:       printf ("R%d+ -> L%d\n", body.reg, body.label1); break;
    case SUBTRACT:  printf ("R%d- -> L%d,L%d\n", body.reg, body.label1, 
                        body.label2); break;
  }
}

void print_bits(int size, void *ptr) {
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

int print_configuration (int *configuration) {
  printf ("L:\t%d\n", configuration[0]);
  for (int i = 1; configuration[i] != -1; i++) {
    printf ("R%d:\t%d\n", i, configuration[i]);
  }
}
