#include "term.h"

#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

static struct termios orig_termios;

/**
 * disables raw mode, commonly enabled via `enable_raw_mode`
 */
static void term_disable_raw_mode(void) {
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void term_enable_raw_mode(void) {
  tcgetattr(STDIN_FILENO, &orig_termios);
  atexit(term_disable_raw_mode);

  struct termios raw = orig_termios;
  tcgetattr(STDIN_FILENO, &raw);

  raw.c_lflag &= ~(ECHO | ICANON);
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void term_disable_buffering(FILE *buf) { setvbuf(buf, NULL, _IONBF, 0); }
void term_enable_buffering(FILE *buf) { setvbuf(buf, NULL, _IOLBF, 0); }
void term_clear(void) { puts(ESCAPE_CODE_CLEAR); }
void term_hide_cursor(void) { puts(ESCAPE_CODE_HIDE_CURSOR); }
void term_show_cursor(void) { puts(ESCAPE_CODE_SHOW_CURSOR); }
