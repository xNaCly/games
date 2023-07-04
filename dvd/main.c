#include "../lib/game.h"
#include "../lib/io.h"
#include "../lib/term.h"
#include <stdio.h>
#include <stdlib.h>

#define WIDTH 32
#define HEIGHT 16
#define BALL '*'

void simulate_ball(char **game) { game[WIDTH / 2][HEIGHT / 2] = BALL; }

int main(void) {
  term_disable_buffering(stdout);
  char **game = game_alloc(WIDTH, HEIGHT);
  game_create_border(game, '|', '-', '+', WIDTH, HEIGHT);
  simulate_ball(game);
  game_render(game, WIDTH, HEIGHT);
  return EXIT_SUCCESS;
}
