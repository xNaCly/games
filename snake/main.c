#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "../lib/game.h"
#include "../lib/io.h"
#include "../lib/term.h"
#include "../lib/util.h"

#define WIDTH 32
#define HEIGHT 48

const int MAX_APPLE = 5;
enum move {
  UP = 0,
  DOWN = 1,
  LEFT = 2,
  RIGHT = 3,
  START = 4,
  END = 5,
  TOP = 6,
  BOTTOM = 7,
};

char KEYBINDS[9][20] = {"w,k - up",
                        "s,j - down",
                        "a,h - left",
                        "d,l - right",
                        "0 - start of row",
                        "$ - end of row",
                        "g - start of column",
                        "G - end of column",
                        "q - quit"};

int SCORE = 0;
int ALIVE = 1;
int SPEED = 1;
int APPLE = 0;
int POSX = 1;
int POSY = 1;

void generate_apple(char **field) {
  if (APPLE >= MAX_APPLE)
    return;
  int x;
  int y;
  do {
    x = rand() % WIDTH - 2;
    y = rand() % HEIGHT - 3;
  } while (x < 1 || y < 1);
  field[x][y] = 'O';
  APPLE++;
}

void fill_playfield(char **field) {
  for (int i = 0; i < WIDTH; i++) {
    for (int j = 0; j < HEIGHT; j++) {
      char c = ' ';

      if ((i == 0 && j == 0) || (i == 0 && j == HEIGHT - 1) ||
          (i == WIDTH - 1 && j == 0) || (i == WIDTH - 1 && j == HEIGHT - 1)) {
        c = '+';
      } else if (i == 0 || i == WIDTH - 1) {
        c = '-';
      } else if (j == 0 || j == HEIGHT - 1) {
        c = '|';
      } else if (j == 1 && i == 1) {
        c = '@';
      }

      field[i][j] = c;
    }
  }
}

void render_playfield(char **field) {
  printf("\033[1;1H\033[2J");
  printf("Keybinds:\n");
  for (size_t i = 0; i < ARRAY_SIZE(KEYBINDS); i++) {
    printf("\t%s\n", KEYBINDS[i]);
  }
  printf("SCORE: %d\n", SCORE);
  game_render(field, WIDTH, HEIGHT);
}

void move(char **field, int direction) {
  field[POSX][POSY] = ' ';

  switch (direction) {
  case START:
    POSY = 1;
    break;
  case END:
    POSY = HEIGHT - 2;
    break;
  case TOP:
    POSX = 1;
    break;
  case BOTTOM:
    POSX = WIDTH - 2;
    break;
  case UP:
    POSX -= SPEED;
    if (POSX < 1)
      ALIVE = 0;
    break;
  case DOWN:
    POSX += SPEED;
    if (POSX >= WIDTH - 2)
      ALIVE = 0;
    break;
  case LEFT:
    POSY -= SPEED;
    if (POSY < 1)
      ALIVE = 0;
    break;
  case RIGHT:
    POSY += SPEED;
    if (POSY >= HEIGHT - 2)
      ALIVE = 0;
    break;
  }

  if (field[POSX][POSY] == 'O') {
    APPLE--;
    SCORE++;
    generate_apple(field);
  }

  field[POSX][POSY] = '@';
}

int handle_input(char **field, char *in) {
  switch (*in) {
  case 'w':
  case 'k':
    move(field, UP);
    break;
  case 's':
  case 'j':
    move(field, DOWN);
    break;
  case 'a':
  case 'h':
    move(field, LEFT);
    break;
  case 'd':
  case 'l':
    move(field, RIGHT);
    break;
  case '0':
    move(field, START);
    break;
  case '$':
    move(field, END);
    break;
  case 'g':
    move(field, TOP);
    break;
  case 'G':
    move(field, BOTTOM);
    break;
  case 'q':
    return -1;
  }
  return 0;
}

int main(void) {
  term_enable_raw_mode();
  term_disable_buffering(stdout);
  srand(time(NULL));

  char **field = game_alloc(WIDTH, HEIGHT);
  fill_playfield(field);
  generate_apple(field);
  render_playfield(field);

  char c;

  while (c = io_read_char(), c != -1) {
    int r = handle_input(field, &c);
    if (!ALIVE) {
      printf("\033[1;1H\033[2J");
      printf("game over, press any key");
      fflush(stdout);
      SCORE = 0;
      ALIVE = 1;
      SPEED = 1;
      APPLE = 0;
      POSX = 1;
      POSY = 1;
      fill_playfield(field);
      generate_apple(field);
      continue;
    }

    if (r != 0) {
      printf("\nexit...\n");
      break;
    }

    c = 0;
    render_playfield(field);
  }

  game_destroy(field, WIDTH);
  return EXIT_SUCCESS;
}
