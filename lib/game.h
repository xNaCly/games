#ifndef GAME_H_
#define GAME_H_

/*
 * allocates `width` rows with `height` elements in `matrix`. Remember to
 * dealloc the matrix when tearing down via the `game_destroy` method
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

/*
 * fills the matrix entries at the border with the given characters
 */
void game_create_border(char **matrix, char border_vertical,
                        char border_horizontal, char corner, int matrix_width,
                        int matrix_heigth);

#endif
