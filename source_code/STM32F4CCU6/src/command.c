#include "command.h"

void manage_command(char command, int value) {
  // printf("OK> %c: %d", command, value);
  switch (command) {
    default:
      // TODO: show error on LEDs
      // printf("ERR> %c: %d", command, value);
      break;
  }
}

void send_command(char command, int value) {
  printf("%c%d\n", command, value);
}