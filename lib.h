#ifndef LIB_H_
#define LIB_H_

/**
 * enables raw input mode, which allows for unbuffered scanning of STDIN
 */
void lib_enable_raw_mode(void);
/**
 * disables raw mode, commonly enabled via `enable_raw_mode`
 */
void lib_disable_raw_mode(void);

#endif
