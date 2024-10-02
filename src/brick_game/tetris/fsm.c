#include "fsm.h"

Signals getSignal(int user_input) {
  Signals rc = NOSIG;

  if (user_input == UP_KEY)
    rc = MOVE_UP;
  else if (user_input == DOWN_KEY)
    rc = MOVE_DOWN;
  else if (user_input == LEFT_KEY)
    rc = MOVE_LEFT;
  else if (user_input == RIGHT_KEY)
    rc = MOVE_RIGHT;
  else if (user_input == ESCAPE_KEY)
    rc = ESCAPE_BTN;
  else if (user_input == START_KEY)
    rc = ENTER_BTN;
  else if (user_input == PAUSE_KEY)
    rc = PAUSE_BTN;
  else if (user_input == ACTION_KEY) {
    rc = ACTION_BTN;
  }

  return rc;
}

void tetrisTimer() {
  Game_t* game = gameT();
  if (game->state == TET_MOVING) {
    clock_t current_time = clock();
    double elapsed_time = ((double)(current_time - game->start)) /
                          CLOCKS_PER_SEC * TETRIS_GAME_SPEED;
    if (elapsed_time > TETRIS_GAME_SPEED / game->game_info->speed) {
      game->start = current_time;
      game->state = TET_SHIFTING;
    }
  }
}

void exitstate() {
  Game_t* game = gameT();

  if (game->game_info->score > game->game_info->high_score) {
    setHighScore();
  }
  game->state = TET_GAMEOVER;
};

void spawn() {
  Game_t* game = gameT();
  game->state = TET_SPAWN;
  game->start = clock();

  // код генерации новой фигуры, проверка что игра не окончена
  spawnFigure();
  if (collision()) {
    exitstate();
  } else {
    game->state = TET_MOVING;
  }
};
void movedown() {
  Game_t* game = gameT();
  game->state = TET_MOVING;
  game->figure->y++;
  if (collision()) {
    game->figure->y--;
    game->state = TET_ATTACHING;
  }
};
void moveright() {
  Game_t* game = gameT();
  game->figure->x++;
  if (collision()) {
    game->figure->x--;
  }
};
void moveleft() {
  Game_t* game = gameT();
  game->figure->x--;
  if (collision()) {
    game->figure->x++;
  }
};

void rotate() { rotateFigure(); }

void shift() {
  Game_t* game = gameT();
  game->state = TET_SHIFTING;

  movedown();
}
void gamepause() {
  Game_t* game = gameT();

  if (game->game_info->pause) {
    game->game_info->pause = 0;
    game->state = TET_MOVING;
  } else {
    game->game_info->pause = 1;
  }
};

void plant() {
  Game_t* game = gameT();
  plantFigure();
  eraseLine();

  game->state = TET_SPAWN;
}
void startstate() {
  Game_t* game = gameT();
  game->state = TET_START;
};

action fsm(Tetris_states state, UserAction_t user_action) {
  if (user_action >= 9) {
    return NULL;
  }
  action result = NULL;

  action fsm_table[6][9] = {
      // START, SPAWN, MOVING, SHIFTING, ATTACHING, GAMEOVER
      // Start, Pause, Terminate, Left, Right, Up, Down, Action, NoAction
      {spawn, NULL, exitstate, NULL, NULL, NULL, NULL, NULL, NULL},     // START
      {spawn, spawn, spawn, spawn, spawn, spawn, spawn, spawn, spawn},  // SPAWN
      {NULL, gamepause, exitstate, moveleft, moveright, NULL, movedown, rotate,
       NULL},  // MOVING
      {shift, shift, shift, shift, shift, shift, shift, shift,
       shift},  // SHIFTING
      {plant, plant, plant, plant, plant, plant, plant, plant,
       plant},                                                      // ATTACHING
      {NULL, NULL, exitstate, NULL, NULL, NULL, NULL, NULL, NULL},  // GAMEOVER
  };

  result = fsm_table[state][user_action];

  return result;
}
