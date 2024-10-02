#include "tests.h"

START_TEST(create_field) {
  int** field = createField();
  ck_assert_int_eq(field[0][0], 0);
  ck_assert_int_eq(field[19][9], 0);

  freeField(field);
}
END_TEST

START_TEST(create_figure) {
  Figure_t* figure = createFigure();
  ck_assert_int_eq(figure->x, 0);
  ck_assert_int_eq(figure->y, 0);
  ck_assert_int_ge(figure->color, 3);
  ck_assert_int_le(figure->color, 7);

  freeFigure(figure);
}
END_TEST

START_TEST(create_game) {
  Game_t* game = gameT();
  createGame();

  ck_assert_int_eq(game->game_info->field[0][0], 0);
  ck_assert_int_eq(game->game_info->field[19][9], 0);
  ck_assert_int_eq(game->next_figure->x, 0);
  ck_assert_int_eq(game->next_figure->y, 0);
  ck_assert_int_ge(game->next_figure->color, 3);
  ck_assert_int_eq(game->game_info->score, 0);
  ck_assert_int_eq(game->game_info->level, 1);

  freeGame();
}
END_TEST

START_TEST(spawn_figure) {
  Game_t* game = gameT();
  createGame();

  spawnFigure();

  ck_assert_ptr_ne(game->figure, game->next_figure);
  ck_assert_int_ne(game->figure->x, game->next_figure->x);
  ck_assert_int_ne(game->figure->y, game->next_figure->y);

  freeGame(game);
}
END_TEST

START_TEST(collision_test) {
  Game_t* game = gameT();
  createGame();

  spawnFigure();

  game->figure->x = MAP_WIDTH;
  game->figure->y = 1;
  ck_assert_int_eq(collision(), 1);

  game->figure->x = -2;
  game->figure->y = 1;
  ck_assert_int_eq(collision(), 1);

  game->figure->x = 2;
  game->figure->y = MAP_HEIGHT;
  ck_assert_int_eq(collision(), 1);

  game->figure->x = 2;
  game->figure->y = -2;
  ck_assert_int_eq(collision(), 1);

  game->figure->x = 2;
  game->figure->y = 5;
  ck_assert_int_eq(collision(), 0);

  freeGame();
}
END_TEST

START_TEST(rotate_figure_test) {
  Game_t* game = gameT();
  createGame();

  spawnFigure();

  game->figure->x = 5;
  game->figure->y = 5;
  game->figure->blocks[0][0] = 1;
  rotateFigure();
  ck_assert_int_ne(game->figure->blocks[0][0], 1);
  ck_assert_int_eq(game->figure->blocks[0][3], 1);

  game->figure->x = 2;
  game->figure->y = 5;
  rotateFigure();
  ck_assert_int_ne(game->figure->blocks[0][0], 1);
  ck_assert_int_eq(game->figure->blocks[3][3], 1);

  freeGame();
}
END_TEST

START_TEST(rotate_figure_negative_test) {
  Game_t* game = gameT();
  createGame();
  spawnFigure();

  game->figure->blocks[0][0] = 1;
  game->figure->x = MAP_WIDTH;
  game->figure->y = 5;
  rotateFigure();
  ck_assert_int_eq(game->figure->blocks[0][0], 1);
  ck_assert_int_ne(game->figure->blocks[0][3], 1);

  freeGame();
}
END_TEST

START_TEST(plant_figure_test) {
  Game_t* game = gameT();
  createGame();
  spawnFigure();

  game->figure->blocks[0][0] = 1;
  game->figure->x = 0;
  game->figure->y = 0;
  plantFigure();
  ck_assert_int_eq(game->game_info->field[0][0], 1);

  freeGame();
}
END_TEST

START_TEST(full_line_test) {
  Game_t* game = gameT();
  createGame();

  ck_assert_int_eq(fullLine(MAP_HEIGHT - 1), 0);
  for (int i = 0; i < MAP_WIDTH; i++) {
    game->game_info->field[MAP_HEIGHT - 1][i] = 1;
  }
  ck_assert_int_eq(fullLine(MAP_HEIGHT - 1), 1);

  freeGame(game);
}
END_TEST

START_TEST(drop_line_test) {
  Game_t* game = gameT();
  createGame();

  game->game_info->field[0][0] = 1;
  dropLine(1);
  ck_assert_int_eq(game->game_info->field[1][0], 1);

  freeGame();
}
END_TEST

START_TEST(erase_line_test) {
  Game_t* game = gameT();
  createGame();

  for (int i = 0; i < MAP_WIDTH; i++) {
    game->game_info->field[MAP_HEIGHT - 1][i] = 1;
    game->game_info->field[MAP_HEIGHT - 2][i] = 1;
  }

  eraseLine();
  ck_assert_int_eq(game->game_info->field[MAP_HEIGHT - 1][0], 0);
  ck_assert_int_eq(game->game_info->field[MAP_HEIGHT - 2][0], 0);
  ck_assert_int_eq(game->game_info->score, 300);

  ck_assert_int_eq(scoring(1), 100);
  ck_assert_int_eq(scoring(2), 300);
  ck_assert_int_eq(scoring(3), 700);
  ck_assert_int_eq(scoring(4), 1500);

  freeGame(game);
}
END_TEST

START_TEST(increase_level_test) {
  Game_t* game = gameT();
  createGame();

  game->game_info->score = 3800;
  increaseLevel();

  ck_assert_int_eq(game->game_info->level, 7);

  game->game_info->score = 13800;
  increaseLevel();
  ck_assert_int_eq(game->game_info->level, 10);

  freeGame();
}
END_TEST

START_TEST(high_score_test) {
  Game_t* game = gameT();
  createGame();
  int score = 3800;
  game->game_info->score = score;
  createHighScore();

  ck_assert_int_eq(getHighScore(), 0);

  setHighScore();
  ck_assert_int_eq(getHighScore(), score);

  freeGame();
}
END_TEST

Suite* test_tetris_function(void) {
  Suite* s = suite_create("\033[45m-=TETRIS_FUNCTIONS=-\033[0m");
  TCase* tc = tcase_create("TETRIS_FUNCTIONS");

  tcase_add_test(tc, create_field);
  tcase_add_test(tc, create_figure);
  tcase_add_test(tc, create_game);
  tcase_add_test(tc, spawn_figure);
  tcase_add_test(tc, collision_test);
  tcase_add_test(tc, rotate_figure_test);
  tcase_add_test(tc, rotate_figure_negative_test);
  tcase_add_test(tc, plant_figure_test);
  tcase_add_test(tc, full_line_test);
  tcase_add_test(tc, drop_line_test);
  tcase_add_test(tc, erase_line_test);
  tcase_add_test(tc, increase_level_test);
  tcase_add_test(tc, high_score_test);

  suite_add_tcase(s, tc);
  return s;
}
