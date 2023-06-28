#ifndef GAME_H_
#define GAME_H_

/*
 * allocates `width` rows with `height` elements in `matrix`
 */
char **game_alloc(int width, int height);

/*
 * writes the given matrix to stdout
 */
void game_render(char **matrix, int width, int height);

/*
 * frees all fields, rows and entries in matrix, sets matrix NULL
 */
void game_destroy(char **matrix, int width);

#endif
