#ifndef IO_H_
#define IO_H_

/*
 * reads a character from standard input, requires a terminal with raw mode
 * enabled, see `lib/term.h#term_enable_raw_mode`
 */
char io_read_char(void);

#define print_err(s)                                                           \
  { fprintf(stderr, "err: %s\n", s); }

#endif
