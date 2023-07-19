#include "../lib/game.h"
#include "../lib/io.h"
#include "../lib/term.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define WIDTH 16
#define HEIGHT 16
/* #define FRAMES 25e5 */
#define FRAMES 25e6
#define BALL '*'

int BALL_X = 1;
int BALL_Y = 1;

void fill_ball(char **game) { game[BALL_X][BALL_Y] = BALL; }

int calc_x() {
  if (BALL_X + 1 > WIDTH - 2)
    return 1;
  return BALL_X + 1;
}
int calc_y() {
  if (BALL_Y + 1 > HEIGHT - 2)
    return 1;
  return BALL_Y + 1;
}

void simulate_ball(char **game) {
  int x = calc_x();
  int y = calc_y();
  game[BALL_X][BALL_Y] = ' ';
  BALL_X = x;
  BALL_Y = y;
  game[BALL_X][BALL_Y] = BALL;
}

char **game;

void clean_up() { game_destroy(game, WIDTH), exit(0); }

int main(void) {
  signal(SIGINT, clean_up);
  term_disable_buffering(stdout);
  term_hide_cursor();

  game = game_alloc(WIDTH, HEIGHT);
  game_create_border(game, '|', '-', '+', WIDTH, HEIGHT);

  for (int i = 0;; i++) {
    if (i == FRAMES) {
      term_clear();
      fill_ball(game);
      game_render(game, WIDTH, HEIGHT);
      simulate_ball(game);
      i = 0;
    }
  }

  clean_up();
  return EXIT_SUCCESS;
}
