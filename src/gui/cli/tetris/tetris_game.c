#include "tetris_game.h"

GameInfo_t updateCurrentState() {
  GameInfo_t game;
  GameInfo_t* game_ptr = gameT()->game_info;

  if (game_ptr) {
    game = *game_ptr;
  }

  return game;
}

void endGame(GameInfo_t* game) {
  if (game == NULL) {
    return;
  }

  while (getUserAction() != Terminate) {
    printEndGame(game);
  }
  freeGame();
}

void tetrisGame() {
  Game_t* game = gameT();

  createGame();

  while (game->state != TET_GAMEOVER) {
    userInput(getUserAction(), true);

    *game->game_info = updateCurrentState();

    printGame();
  }
  endGame(game->game_info);
}