#include "../lib/game.h"
#include "../lib/io.h"
#include "../lib/term.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define WIDTH 120
#define HEIGHT 10
#define JUMP_HEIGTH 4
#define INITIAL_POS_Y 8
#define INITIAL_POS_X WIDTH / 2

int POSY = INITIAL_POS_Y;

void fill_player(char **game) { game[INITIAL_POS_X][POSY] = '@'; }

void clear_field(char **game) {
  for (int i = 0; i < WIDTH; i++) {
    for (int j = 0; j < HEIGHT; j++) {
      game[i][j] = ' ';
    }
  }
}

void fill_border(char **game) {
  for (int i = 0; i < WIDTH; i++) {
    game[i][0] = '-';
    game[i][HEIGHT - 1] = '-';
  }
}

int main(void) {
  term_enable_raw_mode();
  term_disable_buffering(stdout);

  term_clear();
  char **game = game_alloc(WIDTH, HEIGHT);

  puts("press any button to start...");
  fill_border(game);
  game_render(game, WIDTH, HEIGHT);

  char c;
  while (1) {
    clear_field(game);
    if (c = io_read_char(), c != -1) {
      if (c == ' ' && POSY == INITIAL_POS_Y) {
        POSY -= JUMP_HEIGTH;
      } else if (c == 'q') {
        term_clear();
        puts("exiting...");
        break;
      }
    }

    if (POSY < INITIAL_POS_Y)
      POSY += 2;

    term_clear();
    fill_player(game);
    fill_border(game);
    game_render(game, WIDTH, HEIGHT);
  }

  game_destroy(game, WIDTH);
  return EXIT_SUCCESS;
}
