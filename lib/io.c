#include "io.h"
#include <unistd.h>

char io_read_char(void) {
  char r = 0;
  read(STDIN_FILENO, &r, 1);
  return r != 0 ? r : -1;
};
