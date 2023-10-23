#include "../lib/game.h"
#include "../lib/io.h"
#include "../lib/term.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define WIDTH 64
#define HEIGHT 32
#define BALL '*'
#define FPS 144

typedef enum Direction {
  UP_LEFT,
  DOWN_LEFT,
  UP_RIGHT,
  DOWN_RIGHT,
} Direction;

char *DIRECTION_LOOKUP[] = {
    [UP_LEFT] = "UP_LEFT",
    [DOWN_LEFT] = "DOWN_LEFT",
    [UP_RIGHT] = "UP_RIGHT",
    [DOWN_RIGHT] = "DOWN_RIGHT",
};

// contains coordinates and direction of the ball
typedef struct Coord {
  int x;
  int y;
  Direction direction;
} Coord;

typedef struct Game {
  Field field;
  Coord pos;
} Game;

Game GAME;

Direction random_direction() {
  return rand() % sizeof(DIRECTION_LOOKUP) / sizeof(char *);
}

void next_pos(Game *g) {
  int left = 1;
  int right = WIDTH - 2;
  int top = 1;
  int bottom = HEIGHT - 2;

  switch (g->pos.direction) {
  case UP_LEFT:
    g->pos.x -= 1;
    g->pos.y -= 1;
    break;
  case UP_RIGHT:
    g->pos.x -= 1;
    g->pos.y += 1;
    break;
  case DOWN_LEFT:
    g->pos.x += 1;
    g->pos.y -= 1;
    break;
  case DOWN_RIGHT:
    g->pos.x += 1;
    g->pos.y += 1;
    break;
  }

  if (g->pos.x > right || g->pos.x < left || g->pos.y > bottom ||
      g->pos.y < top) {
    g->pos.direction = random_direction();
  }

  if (g->pos.x > right) {
    g->pos.x = right;
  }
  if (g->pos.x < left) {
    g->pos.x = left;
  }
  if (g->pos.y > bottom) {
    g->pos.y = bottom;
  }
  if (g->pos.y < top) {
    g->pos.y = top;
  }
}

void simulate_ball(Game *g) {
  g->field[g->pos.x][g->pos.y] = ' ';
  next_pos(g);
  g->field[g->pos.x][g->pos.y] = BALL;
}

void die() {
  game_destroy(GAME.field, WIDTH);
  term_enable_buffering(stdout);
  term_show_cursor();
  exit(EXIT_SUCCESS);
}

int main(void) {
  signal(SIGINT, die);
  term_hide_cursor();
  term_disable_buffering(stdout);
  srand(time(NULL));

  GAME.field = game_alloc(WIDTH, HEIGHT);
  GAME.pos = (Coord){
      .x = 1,
      .y = 1,
      .direction = random_direction(),
  };
  game_create_border(GAME.field, '|', '-', '+', WIDTH, HEIGHT);

  while (1) {
    term_clear();
    GAME.field[GAME.pos.x][GAME.pos.y] = BALL;
    game_render(GAME.field, WIDTH, HEIGHT);
    simulate_ball(&GAME);
    usleep(FPS / 60 * 1000);
  }

  die();
}
