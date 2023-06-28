#ifndef TERM_H_
#define TERM_H_

/**
 * enables raw input mode, which allows for unbuffered scanning of STDIN via the
 * `lib/io.h` utilities
 */
void term_enable_raw_mode(void);

#endif
