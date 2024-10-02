#ifndef CPP3_BRICKGAME_BRICK_GAME_SNAKE_CONTROLLER_H_
#define CPP3_BRICKGAME_BRICK_GAME_SNAKE_CONTROLLER_H_

#include "model.h"

namespace s21 {
class Controller {
 private:
  Model *model;

 public:
  Controller(Model *m) : model(m){};
  ~Controller(){};

  GameState getState();

  GameInfo_t getGameInfo();
  void startGame();
  void pauseGame();
  void terminateGame();
  void left();
  void right();
  void up();
  void down();
  void action();
  void noAction();
  Apple_t getApple();
};

}  // namespace s21

#endif  // CPP3_BRICKGAME_BRICK_GAME_SNAKE_CONTROLLER_H_