#include "game.h"
#include <stdio.h>
#include <stdlib.h>

char **game_alloc(int width, int height) {
  char **matrix = (char **)malloc(sizeof(char *) * width);
  for (int i = 0; i < width; i++) {
    matrix[i] = (char *)malloc(sizeof(char) * height);
  }
  return matrix;
}

void game_destroy(char **matrix, int width) {
  if (matrix == NULL)
    return;
  for (int i = 0; i < width; i++) {
    free(matrix[i]);
  }
  free(matrix);
  matrix = NULL;
}

void game_render(char **matrix, int width, int height) {
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      printf("%c", matrix[i][j]);
    }
    printf("\n");
  }
};
