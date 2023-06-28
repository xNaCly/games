#include "game.h"
#include "io.h"
#include <stdio.h>
#include <stdlib.h>

char **game_alloc(int width, int height) {
  char **matrix = (char **)malloc(sizeof(char *) * width);
  if (matrix == NULL) {
    print_err("matrix is NULL, allocation failed! - returning NULL");
    return NULL;
  }

  for (int i = 0; i < width; i++) {
    matrix[i] = (char *)malloc(sizeof(char) * height);
  }

  return matrix;
}

void game_destroy(char **matrix, int width) {
  if (matrix == NULL) {
    print_err("matrix already NULL, means it's possibly been freed already");
    return;
  }

  for (int i = 0; i < width; i++) {
    free(matrix[i]);
  }

  free(matrix);
  matrix = NULL;
}

void game_render(char **matrix, int width, int height) {
  if (matrix == NULL) {
    print_err("matrix is NULL, can't render anything");
    return;
  }

  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      printf("%c", matrix[i][j]);
    }
    printf("\n");
  }
};
