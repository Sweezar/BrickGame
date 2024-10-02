#include "snake_game.h"

using namespace s21;
void snakeGame() {
  Model model;
  Controller controller(&model);
  ConsoleView view(&controller);
  view.run();
}