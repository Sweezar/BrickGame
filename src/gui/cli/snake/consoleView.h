#ifndef CPP3_BRICKGAME_BRICK_GAME_SNAKE_CONSOLEVIEW_H_
#define CPP3_BRICKGAME_BRICK_GAME_SNAKE_CONSOLEVIEW_H_

#include <ncurses.h>

#include "../../../brick_game/snake/controller.h"

namespace s21 {
#define KEY_START 10
#define KEY_PAUSE 'p'
#define KEY_TERMINATE 27
#define KEY_ACTION 'w'

#define MAP_WIDTH 10
#define MAP_HEIGHT 20

typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action,
  NoAction
} UserAction_t;

class ConsoleView {
 private:
  Controller *controller;
  GameInfo_t gameInfo;

 public:
  ConsoleView(Controller *c) : controller(c) {
    gameInfo = controller->getGameInfo();
  };

  ~ConsoleView() { endwin(); };

  void run();
  void displayMenu();
  void displayField();
  void displayInfo();
  void displayInputKeys();
  void displayGame();
  void displayGameEnd();
  void pauseHandling();
  void startGameLoop();
  void initColors();

  UserAction_t getUserAction();
  void userInput(UserAction_t user_action, bool hold = true);
};

}  // namespace s21

#endif  // CPP3_BRICKGAME_BRICK_GAME_SNAKE_CONSOLEVIEW_H_