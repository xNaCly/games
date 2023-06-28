#include "../lib/io.h"
#include "../lib/term.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
  term_enable_raw_mode();
  term_disable_buffering(stdout);
  char c;
  while (c = io_read_char(), c != -1) {
    printf("%c", c);
  }
  return EXIT_SUCCESS;
}
