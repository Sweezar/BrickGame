#include "tests.h"

START_TEST(get_signal) {
  ck_assert_int_eq(getSignal(UP_KEY), MOVE_UP);
  ck_assert_int_eq(getSignal(DOWN_KEY), MOVE_DOWN);
  ck_assert_int_eq(getSignal(LEFT_KEY), MOVE_LEFT);
  ck_assert_int_eq(getSignal(RIGHT_KEY), MOVE_RIGHT);
  ck_assert_int_eq(getSignal(ESCAPE_KEY), ESCAPE_BTN);
  ck_assert_int_eq(getSignal(START_KEY), ENTER_BTN);
  ck_assert_int_eq(getSignal(PAUSE_KEY), PAUSE_BTN);
  ck_assert_int_eq(getSignal(ACTION_KEY), ACTION_BTN);
  ck_assert_int_eq(getSignal(1), NOSIG);
}
END_TEST

START_TEST(timer_test) {
  Game_t* game = gameT();
  createGame();
  game->state = TET_MOVING;
  tetrisTimer();
  ck_assert_int_eq(game->state, TET_MOVING);

  freeGame();
}
END_TEST

START_TEST(exitstate_test) {
  Game_t* game = gameT();
  createGame();
  game->state = TET_START;
  exitstate();

  ck_assert_int_eq(game->state, TET_GAMEOVER);

  freeGame();
}
END_TEST

START_TEST(spawn_test_1) {
  Game_t* game = gameT();
  createGame();
  game->state = TET_START;
  for (int i = 0; i < MAP_WIDTH;
       i++) {  // заполняю первую линию поля, чтобы вызвать столкновение фигуры
    game->game_info->field[0][i] = 1;
  }
  spawn();

  ck_assert_int_eq(game->state, TET_GAMEOVER);

  freeGame();
}
END_TEST

START_TEST(spawn_test_2) {
  Game_t* game = gameT();
  createGame();
  game->state = TET_START;
  spawn();

  ck_assert_int_eq(game->state, TET_MOVING);
  ck_assert_int_ne(game->figure->x, 0);

  freeGame();
}
END_TEST

START_TEST(movedown_test_1) {
  Game_t* game = gameT();
  createGame();
  spawn();

  int y = game->figure->y;

  movedown();
  movedown();
  movedown();
  ck_assert_int_eq(game->state, TET_MOVING);
  ck_assert_int_eq(game->figure->y, y + 3);

  freeGame();
}
END_TEST

START_TEST(movedown_test_2) {
  Game_t* game = gameT();
  createGame();
  spawn();

  for (int i = 0; i < MAP_WIDTH;
       i++) {  // заполняю 4ю линию поля, чтобы вызвать столкновение фигуры
    game->game_info->field[5][i] = 1;
  }

  movedown();
  movedown();
  movedown();
  movedown();
  movedown();
  ck_assert_int_eq(game->state, TET_ATTACHING);
  ck_assert_int_gt(game->figure->y, 0);

  freeGame(game);
}
END_TEST

START_TEST(moveright_test_1) {
  Game_t* game = gameT();
  createGame();
  spawn();

  int x = game->figure->x;
  moveright();

  ck_assert_int_eq(game->figure->x, x + 1);

  freeGame();
}
END_TEST

START_TEST(moveright_test_2) {
  Game_t* game = gameT();
  createGame();
  spawn();
  game->figure->x = MAP_WIDTH;

  int x = game->figure->x;
  moveright();

  ck_assert_int_eq(game->figure->x, x);

  freeGame();
}
END_TEST

START_TEST(moveleft_test_1) {
  Game_t* game = gameT();
  createGame();
  spawn();

  int x = game->figure->x;
  moveleft();

  ck_assert_int_eq(game->figure->x, x - 1);

  freeGame();
}
END_TEST

START_TEST(moveleft_test_2) {
  Game_t* game = gameT();
  createGame();
  spawn();
  game->figure->x = -1;

  int x = game->figure->x;
  moveleft();

  ck_assert_int_eq(game->figure->x, x);

  freeGame();
}
END_TEST

START_TEST(rotate_test_1) {
  Game_t* game = gameT();
  createGame();
  spawn();
  movedown();

  game->figure->blocks[0][0] = 1;
  rotate();

  ck_assert_int_eq(game->figure->blocks[0][3], 1);

  freeGame();
}
END_TEST

START_TEST(rotate_test_2) {
  Game_t* game = gameT();
  createGame();
  spawn();
  game->figure->x = -1;

  game->figure->blocks[0][0] = 1;
  rotate();

  ck_assert_int_eq(game->figure->blocks[0][0], 1);

  freeGame();
}
END_TEST

START_TEST(shift_test) {
  Game_t* game = gameT();
  createGame();
  spawn();
  game->figure->y = 0;
  shift();

  ck_assert_int_eq(game->figure->y, 1);

  freeGame();
}
END_TEST

START_TEST(pause_test) {
  Game_t* game = gameT();
  createGame();

  gamepause();
  ck_assert_int_eq(game->game_info->pause, 1);

  gamepause();
  ck_assert_int_eq(game->game_info->pause, 0);

  freeGame();
}
END_TEST

START_TEST(plant_test) {
  Game_t* game = gameT();
  createGame();
  spawn();

  plant();
  ck_assert_int_eq(game->state, TET_SPAWN);

  spawn();
  ck_assert_int_eq(game->state, TET_GAMEOVER);

  freeGame();
}
END_TEST

START_TEST(fsm_test) {
  action act = fsm(TET_MOVING, Down);
  ck_assert_ptr_eq(act, movedown);
}
END_TEST

Suite* test_tetris_fsm(void) {
  Suite* s = suite_create("\033[45m-=TETRIS_FSM=-\033[0m");
  TCase* tc = tcase_create("TETRIS_FSM");

  tcase_add_test(tc, get_signal);
  tcase_add_test(tc, timer_test);
  tcase_add_test(tc, exitstate_test);
  tcase_add_test(tc, spawn_test_1);
  tcase_add_test(tc, spawn_test_2);
  tcase_add_test(tc, movedown_test_1);
  tcase_add_test(tc, movedown_test_2);
  tcase_add_test(tc, moveright_test_1);
  tcase_add_test(tc, moveright_test_2);
  tcase_add_test(tc, moveleft_test_1);
  tcase_add_test(tc, moveleft_test_2);
  tcase_add_test(tc, rotate_test_1);
  tcase_add_test(tc, rotate_test_2);
  tcase_add_test(tc, shift_test);
  tcase_add_test(tc, pause_test);
  tcase_add_test(tc, plant_test);
  tcase_add_test(tc, fsm_test);

  suite_add_tcase(s, tc);
  return s;
}