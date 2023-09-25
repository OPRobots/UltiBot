#include "usart.h"

// TODO: gestionar el printf normal por el USART1 y ver como enviar los datos al USART6 para FOC
//  int _write(int file, char *ptr, int len)
//  {
//  	int i = 0;

// 	/*
// 	 * Write "len" of char from "ptr" to file id "file"
// 	 * Return number of char written.
// 	 *
// 	 * Only work for STDOUT, STDIN, and STDERR
// 	 */
// 	if (file > 2) {
// 		return -1;
// 	}
// 	while (*ptr && (i < len)) {
// 		usart_send_blocking(USART1, *ptr);
// 		i++;
// 		ptr++;
// 	}
// 	return i;
// }

int _write(int file, char *ptr, int len) {
  int i = 0;

  /*
   * Write "len" of char from "ptr" to file id "file"
   * Return number of char written.
   *
   * Only work for STDOUT, STDIN, and STDERR
   */
  if (file > 2) {
    return -1;
  }
  while (*ptr && (i < len)) {
    usart_send_blocking(USART1, *ptr);
    i++;
    ptr++;
  }
  return i;
}