#include "lib.h"

#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

struct termios orig_termios;

void lib_disable_raw_mode(void) {
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void lib_enable_raw_mode(void) {
  tcgetattr(STDIN_FILENO, &orig_termios);
  atexit(lib_disable_raw_mode);

  struct termios raw = orig_termios;
  tcgetattr(STDIN_FILENO, &raw);

  raw.c_lflag &= ~(ECHO | ICANON);
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}
