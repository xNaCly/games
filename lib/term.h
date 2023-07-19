#ifndef TERM_H_
#define TERM_H_

#include <stdio.h>

#define ESCAPE_CODE_CLEAR "\033[1;1H\033[2J"
#define ESCAPE_CODE_HIDE_CURSOR "\033[?25l"

/**
 * enables raw input mode, which allows for unbuffered scanning of STDIN via
 * the `lib/io.h` utilities
 */
void term_enable_raw_mode(void);

/**
 * sets buffering for `buf` to `_IONBF` (no buffering)
 */
void term_disable_buffering(FILE *buf);

/**
 * sets buffering for `buf` to `_IOLBF` (line buffering)
 */
void term_enable_buffering(FILE *buf);

/**
 * sends 'ESCAPE_CODE_CLEAR' to the terminal, this should clear the screen
 */
void term_clear(void);

/**
 * sends 'ESCAPE_CODE_HIDE_CURSOR' to the terminal, hides the cursor
 */
void term_hide_cursor(void);

#endif
