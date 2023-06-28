#ifndef TERM_H_
#define TERM_H_

#include <stdio.h>

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

#endif
