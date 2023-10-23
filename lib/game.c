#include "game.h"
#include "io.h"
#include <stdio.h>
#include <stdlib.h>

Field game_alloc(int width, int height) {
  Field matrix = malloc(sizeof(char *) * width);
  if (matrix == NULL) {
    io_print_err("matrix is NULL, allocation failed! - returning NULL");
    return NULL;
  }

  for (int i = 0; i < width; i++) {
    matrix[i] = (char *)malloc(sizeof(char) * height);
  }

  return matrix;
}

void game_render(Field matrix, int width, int height) {
  if (matrix == NULL) {
    io_print_err("matrix is NULL, can't render anything");
    return;
  }

  /*
   The matrix is an array of arrays, think of a two dimensional cartesian
   coordinate system. This means the allocation step creates an array of size
   width (the x-axis in our example) and size width arrays in it, each one an
   array of size height (the y-axis in our example). Due to the nature of the
   terminal we iterate over the width and print every y-axis array separated
   by a newline. This flips the x- and y-axis and does not match our
   allocation or our mental model, which can be a huge pain. This can be
   fixed by inverting the iteration from width and height to height and width:
  */
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      printf("%c", matrix[j][i]);
    }
    puts("");
  }
}

void game_destroy(Field matrix, int width) {
  if (matrix == NULL) {
    io_print_err("matrix already NULL, means it's possibly been freed already");
    return;
  }

  for (int i = 0; i < width; i++) {
    free(matrix[i]);
  }

  free(matrix);
}

void game_create_border(Field matrix, char border_vertical,
                        char border_horizontal, char corner, int matrix_width,
                        int matrix_heigth) {
  for (int i = 0; i < matrix_width; i++) {
    for (int j = 0; j < matrix_heigth; j++) {
      char c = ' ';
      if ((i == 0 && j == 0) || (i == 0 && j == matrix_heigth - 1) ||
          (i == matrix_width - 1 && j == 0) ||
          (i == matrix_width - 1 && j == matrix_heigth - 1)) {
        c = corner;
      } else if (i == 0 || i == matrix_width - 1) {
        c = border_vertical;
      } else if (j == 0 || j == matrix_heigth - 1) {
        c = border_horizontal;
      }
      if (c)
        matrix[i][j] = c;
    }
  };
}
