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
  // printf("%c%d\n", command, value);
  usart_send_blocking(USART6, command);
  usart_send_blocking(USART6, value);
  usart_send_blocking(USART6, '\n');
}