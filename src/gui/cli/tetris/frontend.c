#include "frontend.h"

void initColors() {
  init_pair(1, COLOR_YELLOW, COLOR_YELLOW);
  init_pair(2, COLOR_WHITE, COLOR_WHITE);
  init_pair(3, COLOR_GREEN, COLOR_GREEN);
  init_pair(4, COLOR_RED, COLOR_RED);
  init_pair(5, COLOR_MAGENTA, COLOR_MAGENTA);
  init_pair(6, COLOR_CYAN, COLOR_CYAN);
  init_pair(7, COLOR_BLUE, COLOR_BLUE);
}

void printFigure(Game_t* game, int i, int j, int* color) {
  if (game->figure && game->figure->blocks != NULL) {
    int x = j - game->figure->x;
    int y = i - game->figure->y;

    if (x >= 0 && x < FIGURE_SIZE && y >= 0 && y < FIGURE_SIZE) {
      if (game->figure->blocks[y][x] == 1) {
        *color = game->figure->color;
      }
    }
  }
}

void printStartScreen() {
  mvprintw(MAP_HEIGHT / 2 - 5, 5, "Change game:");
  mvprintw(MAP_HEIGHT / 2 - 1, 6, "1.TETRIS");
  mvprintw(MAP_HEIGHT / 2, 6, "2.SNAKE");
}

void printField() {
  Game_t* game = gameT();
  int** field = game->game_info->field;
  int m = 0;

  for (int i = 0; i < MAP_HEIGHT; i++) {
    for (int j = 0; j < MAP_WIDTH; j++) {
      int color = 1;
      if (field[i][j] == 0) {
        color = 2;
      }

      printFigure(game, i, j, &color);

      attron(COLOR_PAIR(color));
      mvaddch(i, j + m, ' ');
      m++;
      mvaddch(i, j + m, ' ');
      attroff(COLOR_PAIR(color));
    }
    m = 0;
  }
}

void printNextFigure() {
  Game_t* game = gameT();
  int m = 0;

  mvprintw(0, MAP_WIDTH * 2 + 1, "Next figure");
  for (int i = 0; i < FIGURE_SIZE; i++) {
    for (int j = 0; j < FIGURE_SIZE; j++) {
      int color = game->next_figure->color;
      if (game->next_figure->blocks[i][j] == 0) {
        color = 0;
      }
      attron(COLOR_PAIR(color));
      mvaddch(i + 1, j + (MAP_WIDTH * 2) + 1 + m, ' ');
      m++;
      mvaddch(i + 1, j + (MAP_WIDTH * 2) + 1 + m, ' ');
      attroff(COLOR_PAIR(color));
    }
    m = 0;
  }
}

void printInfo() {
  Game_t* game = gameT();

  mvprintw(6, MAP_WIDTH * 2 + 1, "Score: %5d", game->game_info->score);
  mvprintw(7, MAP_WIDTH * 2 + 1, "Level: %2d", game->game_info->level);
  mvprintw(8, MAP_WIDTH * 2 + 1, "Speed: %2d", game->game_info->speed);
  mvprintw(9, MAP_WIDTH * 2 + 1, "High-score: %d", game->game_info->high_score);

  if (game->game_info->pause) {
    mvprintw(MAP_HEIGHT / 2, 0, "Press SPACE to start");
  }
  if (game->state == TET_START) {
    mvprintw(MAP_HEIGHT / 2, 0, "Press ENTER to start");
    nodelay(stdscr, TRUE);
  }
}

void printKeys() {
  mvprintw(11, MAP_WIDTH * 2 + 1, "Pause key  : SPACE");
  mvprintw(12, MAP_WIDTH * 2 + 1, "Start key  : ENTER");
  mvprintw(13, MAP_WIDTH * 2 + 1, "Action key : %c", ACTION_KEY);
  mvprintw(14, MAP_WIDTH * 2 + 1, "Move left  : Left key");
  mvprintw(15, MAP_WIDTH * 2 + 1, "Move right : Right key");
  mvprintw(16, MAP_WIDTH * 2 + 1, "Move down  : Down key");
  mvprintw(17, MAP_WIDTH * 2 + 1, "Exit game  : ESC");
}

void printGame() {
  printField();
  printNextFigure();

  printInfo();
  printKeys();
}

void printEndGame(GameInfo_t* game) {
  if (game->high_score < game->score) {
    mvprintw(MAP_HEIGHT / 2 - 5, 5, "You are the");
    mvprintw(MAP_HEIGHT / 2 - 4, 7, "CHAMPION");
  }
  mvprintw(MAP_HEIGHT / 2 - 2, 6, "Game over");
  mvprintw(MAP_HEIGHT / 2, 0, "  You scored : %d     ", game->score);
  mvprintw(MAP_HEIGHT / 2 + 1, 2, "High-score : %d", game->high_score);

  mvprintw(MAP_HEIGHT / 2 + 3, 6, "Press Esc");
}