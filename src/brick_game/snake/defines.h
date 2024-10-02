#ifndef CPP3_BRICKGAME_BRICK_GAME_SNAKE_DEFINES_H_
#define CPP3_BRICKGAME_BRICK_GAME_SNAKE_DEFINES_H_

#include <vector>

#include "../tetris/objects.h"

#define GAMEWIN -2
#define GAMEOVER -1
#define GAMESTART 2
#define PAUSE 1
#define UNPAUSE 0

#define MAP_WIDTH 10
#define MAP_HEIGHT 20

#define MAX_GAME_SPEED 10
#define MAX_GAME_LEVEL 10
#define SNAKE_GAME_SPEED 1.0
#define ORIGIN_SNAKE_LENGHT 3
#define MAX_SNAKE_LENGTH 200

#define SCORE_FOR_LEVEL_UP 5
#define SNAKE_HIGH_SCORE_FILE "snake_highscore.txt"

typedef enum { UP_DIR, DOWN_DIR, LEFT_DIR, RIGHT_DIR } Direction;

typedef enum {
  STARTGAME,
  MOVING,
  EATING,
  SHIFTING,
  COLLISION,
  ENDGAME,
} GameState;

typedef struct Point_t {
  int x;
  int y;

  bool operator==(const Point_t& other) const {
    return x == other.x && y == other.y;
  }
  bool operator!=(const Point_t& other) const {
    return x != other.x || y != other.y;
  }
} Point_t;

typedef struct Apple_t {
  Point_t position;

  bool operator==(const Apple_t& other) const {
    return position == other.position;
  }
  bool operator!=(const Apple_t& other) const {
    return position != other.position;
  }

} Apple_t;

typedef struct Snake_t {
  std::vector<Point_t> body;
  Direction direction;
  int length;

  bool operator==(const Snake_t& other) const { return body == other.body; }
  bool operator!=(const Snake_t& other) const { return body != other.body; }
} Snake_t;

#endif
