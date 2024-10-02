#include "consoleView.h"

namespace s21 {
void ConsoleView::run() {
  displayMenu();
  startGameLoop();
  displayGameEnd();
}

void ConsoleView::displayMenu() {
  while (gameInfo.pause == GAMESTART) {
    userInput(getUserAction());
    mvprintw(1, 1, "SNAKE game");
    mvprintw(2, 1, "Press Enter to Start");
    refresh();
  }
  clear();
}

void ConsoleView::displayField() {
  int** field = gameInfo.field;
  int m = 0;
  Point_t applePos = controller->getApple().position;

  for (int i = 0; i < MAP_HEIGHT; i++) {
    for (int j = 0; j < MAP_WIDTH; j++) {
      int color = 1;
      if (applePos.x == j && applePos.y == i) {
        color = 3;
      }
      if (field[i][j] == 0) {
        color = 2;
      }

      attron(COLOR_PAIR(color));
      mvaddch(i, j + m, ' ');
      m++;
      mvaddch(i, j + m, ' ');
      attroff(COLOR_PAIR(color));
    }
    m = 0;
  }
}

void ConsoleView::displayInfo() {
  mvprintw(1, MAP_WIDTH * 2 + 3, "Score: %d", gameInfo.score);
  mvprintw(2, MAP_WIDTH * 2 + 3, "High score: %d", gameInfo.high_score);
  mvprintw(3, MAP_WIDTH * 2 + 3, "Level: %d", gameInfo.level);
  mvprintw(4, MAP_WIDTH * 2 + 3, "Speed: %d", gameInfo.speed);
}

void ConsoleView::displayInputKeys() {
  mvprintw(8, MAP_WIDTH * 2 + 3, "Pause: %c", KEY_PAUSE);
  mvprintw(9, MAP_WIDTH * 2 + 3, "Exit: ESC");
  mvprintw(10, MAP_WIDTH * 2 + 3, "Action: %c", KEY_ACTION);
  mvprintw(11, MAP_WIDTH * 2 + 3, "Up: up");
  mvprintw(12, MAP_WIDTH * 2 + 3, "Down: down");
  mvprintw(13, MAP_WIDTH * 2 + 3, "Left: left");
  mvprintw(14, MAP_WIDTH * 2 + 3, "Right: right");
}

void ConsoleView::displayGame() {
  displayField();
  displayInfo();
  displayInputKeys();
}

void ConsoleView::displayGameEnd() {
  while (getch() != KEY_TERMINATE) {
    if (gameInfo.pause == GAMEWIN) {
      mvprintw(MAP_HEIGHT / 2, 6, "YOU WIN");
    }
    mvprintw(MAP_HEIGHT / 2 + 1, 5, "GAME OVER");
    refresh();
  }

  clear();
}

void ConsoleView::pauseHandling() {
  if (gameInfo.pause == PAUSE) {
    nodelay(stdscr, FALSE);
    mvprintw(MAP_HEIGHT / 2, 8, "PAUSE");
  } else {
    nodelay(stdscr, TRUE);
  }
}

void ConsoleView::startGameLoop() {
  while (gameInfo.pause != GAMEOVER && gameInfo.pause != GAMEWIN) {
    pauseHandling();
    userInput(getUserAction());
    displayGame();
    refresh();
  }
  clear();
}

void ConsoleView::initColors() {
  init_pair(1, COLOR_YELLOW, COLOR_YELLOW);
  init_pair(2, COLOR_WHITE, COLOR_WHITE);
  init_pair(3, COLOR_GREEN, COLOR_GREEN);
}

UserAction_t ConsoleView::getUserAction() {
  int ch = getch();
  switch (ch) {
    case KEY_START:
      return Start;
    case KEY_PAUSE:
      return Pause;
    case KEY_TERMINATE:
      return Terminate;
    case KEY_LEFT:
      return Left;
    case KEY_RIGHT:
      return Right;
    case KEY_UP:
      return Up;
    case KEY_DOWN:
      return Down;
    case KEY_ACTION:
      return Action;
    default:
      return NoAction;
  }
}

void ConsoleView::userInput(UserAction_t user_action, bool hold) {
  if (hold) switch (user_action) {
      case Start:
        controller->startGame();
        break;
      case Pause:
        controller->pauseGame();
        break;
      case Terminate:
        controller->terminateGame();
        break;
      case Left:
        controller->left();
        break;
      case Right:
        controller->right();
        break;
      case Up:
        controller->up();
        break;
      case Down:
        controller->down();
        break;
      case Action:
        controller->action();
        break;
      default:
        controller->noAction();
        break;
    }

  this->gameInfo = controller->getGameInfo();
}
}  // namespace s21