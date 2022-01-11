#ifndef MAIN_H
#define MAIN_H

enum type {
  ADD,
  SUBTRACT,
  HALT
};

struct body {
  enum type type; 
  int reg;
  int label1;
  int label2;
};

struct pair {
  int first;
  int second;
};

#endif
