#include "execute.h"
#include "pretty_print.h"

void execute_program (int *configuration, struct body *program) {
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
