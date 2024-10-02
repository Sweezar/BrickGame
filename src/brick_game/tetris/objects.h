#ifndef OBJECTS_H_
#define OBJECTS_H_

#include <time.h>

#define WIN_INIT()          \
  {                         \
    initscr();              \
    start_color();          \
    initColors();           \
    cbreak();               \
    noecho();               \
    keypad(stdscr, TRUE);   \
    nodelay(stdscr, TRUE);  \
    scrollok(stdscr, TRUE); \
    curs_set(0);            \
  }

#define MAP_WIDTH 10
#define MAP_HEIGHT 20
#define FIGURE_SIZE 4
#define FIGURE_TYPES_COUNT 7

#define TETRIS_GAME_SPEED 1000

#define MAX_LEVELS 10
#define LEVEL_THRESHOLD 600
#define SPEED_FACTOR 90

#define ACTION_KEY 'w'
#define ESCAPE_KEY 27
#define START_KEY 10
#define PAUSE_KEY 32
#define UP_KEY 0403
#define DOWN_KEY 0402
#define LEFT_KEY 0404
#define RIGHT_KEY 0405

#define START_LEVEL 1
#define START_SPEED 1

#define TETRIS_HIGH_SCORE_FILE "tetris_high_score.txt"

typedef enum {
  TET_START = 0,
  TET_SPAWN,
  TET_MOVING,
  TET_SHIFTING,
  TET_ATTACHING,
  TET_GAMEOVER
} Tetris_states;

typedef enum {
  NOSIG = 0,
  MOVE_UP,
  MOVE_DOWN,
  MOVE_RIGHT,
  MOVE_LEFT,
  ESCAPE_BTN,
  ENTER_BTN,
  PAUSE_BTN,
  ACTION_BTN
} Signals;

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

typedef struct {
  int x;
  int y;
  int** blocks;
  int color;
} Figure_t;

typedef struct {
  int** field;
  int** next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;

typedef struct {
  GameInfo_t* game_info;
  Figure_t* figure;
  Figure_t* next_figure;
  Tetris_states state;
  clock_t start;
} Game_t;

typedef void (*action)();

#endif