#include "../lib/game.h"
#include "../lib/io.h"
#include "../lib/term.h"
#include <stdio.h>
#include <stdlib.h>

#define WIDTH 32
#define HEIGHT 16
#define BALL '*'

void simulate_ball(char **game) {}

int main(void) {
  term_disable_buffering(stdout);
  char **game = game_alloc(WIDTH, HEIGHT);
  while (1) {
    term_clear();
    simulate_ball(game);
  }
  return EXIT_SUCCESS;
}
