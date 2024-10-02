#include "input.h"

UserAction_t getUserAction() {
  int ch = getch();
  Signals sig = getSignal(ch);
  UserAction_t userAction = NoAction;

  switch (sig) {
    case MOVE_UP:
      break;

    case MOVE_DOWN:
      userAction = Down;
      break;

    case MOVE_LEFT:
      userAction = Left;
      break;

    case MOVE_RIGHT:
      userAction = Right;
      break;

    case ESCAPE_BTN:
      userAction = Terminate;
      break;

    case ENTER_BTN:
      userAction = Start;
      break;

    case PAUSE_BTN:
      userAction = Pause;
      break;

    case ACTION_BTN:
      userAction = Action;
      break;

    case NOSIG:
    default:
      userAction = NoAction;
      break;
  }

  return userAction;
}

void userInput(UserAction_t user_action, bool hold) {
  action act = NULL;
  Game_t* game = gameT();
  if (!game->game_info->pause) {
    tetrisTimer();

    act = fsm(game->state, user_action);
  } else {
    if (user_action == Pause || user_action == Terminate) {
      act = fsm(game->state, user_action);
    }
  }

  if (act && hold) act();
};

int changeGame() {
  int ch = getch();
  switch (ch) {
    case '1':
      return TETRIS_GAME;

    case '2':
      return SNAKE_GAME;

    default:
      return 0;
  }
}