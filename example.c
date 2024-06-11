#include "dart_interface.h"
#include <stdio.h>
#include "stdlib.h"

int main(int argc, char *argv[]) {
  int v = are_equal("./data/named/eminem_1.png", "./data/named/eminem_2.png");

  printf("Eminem is eminem? %s\n", v ? "true" : "false");
  return EXIT_SUCCESS;
}
