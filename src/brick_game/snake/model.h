#ifndef CPP3_BRICKGAME_BRICK_GAME_SNAKE_MODEL_H_
#define CPP3_BRICKGAME_BRICK_GAME_SNAKE_MODEL_H_

#include <fstream>
#include <iostream>

#include "defines.h"

namespace s21 {
class Model {
 public:
  Model();
  ~Model();

  GameInfo_t getInfo();
  Direction getDirection();
  Apple_t getApple();
  Snake_t getSnake();
  GameState getState();

  void setState(GameState state);
  void setApple(Apple_t apple);
  void setSnake(Snake_t snake);

  void startGame();
  void changeDirectionLeft();
  void changeDirectionRight();
  void changeDirectionUp();
  void changeDirectionDown();
  void moveSnakeForward();
  void shifting();
  void pauseGame();
  void endGame();

 private:
  GameInfo_t _gameinfo;
  Apple_t _apple;
  Snake_t _snake;
  GameState _state;
  clock_t _start;

  void init();
  void initField();
  void deleteField();
  void resetField();
  void initGameInfo();

  void initApple();
  void addApple();
  void generateApplePosition();
  bool checkAppleGeneration();
  bool checkEatApple();
  void eatApple();

  void initSnake();
  void addSnake();
  void shiftSnakePoints(Point_t point);
  bool checkCollideField(Point_t point);
  bool checkCollideSnake(Point_t point);
  bool collide(Point_t point);
  void moveSnake();

  void timer();
  void increaseScore();
  void increaseLevel();
  void increaseSpeed();

  void updateGameField();
  void updateNewPoint(Point_t point);
  void checkWin();

  void openHighScoreFile();
  void setHighScore();
};  // Model
}  // namespace s21

#endif  // CPP3_BRICKGAME_BRICK_GAME_SNAKE_MODEL_H_
