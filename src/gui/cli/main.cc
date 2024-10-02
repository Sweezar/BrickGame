#include "tetris/tetris_game.h"
#include "snake/snake_game.h"

void startScreenLoop(int* game);

int main() {
  WIN_INIT();
  int game = 0;
  startScreenLoop(&game);
  if(game == TETRIS_GAME) {
    tetrisGame();
  } else if(game == SNAKE_GAME) {
    snakeGame();
  }
  endwin();

  return 0;
}

void startScreenLoop(int* game) {
  while (!*game) {
    *game = changeGame();
    printStartScreen();
  }
}