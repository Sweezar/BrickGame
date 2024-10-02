#include "tetris.h"

int* chooseFigureTypes() {
  int* type = (int*)calloc(FIGURE_SIZE * FIGURE_SIZE, sizeof(int));
  int rand_type = rand() % FIGURE_TYPES_COUNT;
  int figures[FIGURE_TYPES_COUNT][FIGURE_SIZE * FIGURE_SIZE] = {
      {0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0},
      {0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0}};

  for (int i = 0; i < FIGURE_SIZE * FIGURE_SIZE; i++) {
    type[i] = figures[rand_type][i];
  }

  return type;
}

void freeFigureType(int* type) {
  if (type) {
    free(type);
  }
}

int** createField() {
  int** field = (int**)calloc(MAP_HEIGHT, sizeof(int*));
  for (int i = 0; i < MAP_HEIGHT; i++) {
    field[i] = (int*)calloc(MAP_WIDTH, sizeof(int));
  }

  return field;
}

void freeField(int** field) {
  if (field) {
    for (int i = 0; i < MAP_HEIGHT; i++) {
      free(field[i]);
    }
    free(field);
  }
}

Figure_t* createFigure() {
  Figure_t* figure = (Figure_t*)calloc(1, sizeof(Figure_t));
  int* figure_type = chooseFigureTypes();
  figure->x = 0;
  figure->y = 0;
  figure->blocks = (int**)calloc(FIGURE_SIZE, sizeof(int*));
  for (int i = 0; i < FIGURE_SIZE; i++) {
    figure->blocks[i] = (int*)calloc(FIGURE_SIZE, sizeof(int));
    for (int j = 0; j < FIGURE_SIZE; j++) {
      figure->blocks[i][j] = figure_type[i * FIGURE_SIZE + j];
    }
  }
  figure->color =
      (rand() % 5) + 3;  //  Всего 7 цветов, 2 зарезервированы под поле
  freeFigureType(figure_type);

  return figure;
}

void freeFigure(Figure_t* figure) {
  if (figure) {
    for (int i = 0; i < FIGURE_SIZE; i++) {
      free(figure->blocks[i]);
    }
    free(figure->blocks);
    free(figure);
  }
}

void createGame() {
  Game_t* game = gameT();
  game->game_info = (GameInfo_t*)calloc(1, sizeof(GameInfo_t));
  game->game_info->field = createField();
  game->next_figure = createFigure();
  game->figure = NULL;
  game->state = TET_START;
  game->game_info->speed = START_SPEED;
  game->start = 0;
  game->game_info->level = START_LEVEL;
  game->game_info->high_score = getHighScore();
}

void freeGameInfo(GameInfo_t* info) {
  if (info) {
    free(info);
  }
}
void freeGame() {
  Game_t* game = gameT();

  if (game) {
    freeField(game->game_info->field);
    freeFigure(game->figure);
    freeFigure(game->next_figure);
    freeGameInfo(game->game_info);
  }
}

Game_t* gameT() {
  static Game_t game;

  return &game;
}

void spawnFigure() {
  Game_t* game = gameT();

  freeFigure(game->figure);
  game->figure = game->next_figure;
  game->figure->x = MAP_WIDTH / 2 - FIGURE_SIZE / 2;
  game->figure->y = -1;
  if (game->figure->blocks[0][1]) {
    game->figure->y = 0;
  }
  game->next_figure = createFigure();
}

int collision() {
  Game_t* game = gameT();

  Figure_t* figure = game->figure;
  int** field = game->game_info->field;

  for (int i = 0; i < FIGURE_SIZE; i++) {
    for (int j = 0; j < FIGURE_SIZE; j++) {
      if (figure->blocks[i][j] != 0) {
        int fx = figure->x + j;
        int fy = figure->y + i;
        if (fx < 0 || fx >= MAP_WIDTH || fy < 0 || fy >= MAP_HEIGHT) {
          return 1;
        }
        if (field[fy][fx] != 0) {
          return 1;
        }
      }
    }
  }

  return 0;
}

void rotateFigure() {
  Game_t* game = gameT();
  Figure_t* figure = game->figure;

  int old_figure[FIGURE_SIZE][FIGURE_SIZE];
  for (int i = 0; i < FIGURE_SIZE; i++) {
    for (int j = 0; j < FIGURE_SIZE; j++) {
      old_figure[i][j] = figure->blocks[i][j];
    }
  }
  for (int i = 0; i < FIGURE_SIZE; i++) {
    for (int j = 0; j < FIGURE_SIZE; j++) {
      figure->blocks[i][j] = old_figure[FIGURE_SIZE - j - 1][i];
    }
  }

  if (collision()) {
    for (int i = 0; i < FIGURE_SIZE; i++) {
      for (int j = 0; j < FIGURE_SIZE; j++) {
        figure->blocks[i][j] = old_figure[i][j];
      }
    }
  }
}

void plantFigure() {
  Game_t* game = gameT();
  Figure_t* figure = game->figure;
  int** field = game->game_info->field;

  for (int i = 0; i < FIGURE_SIZE; i++) {
    for (int j = 0; j < FIGURE_SIZE; j++) {
      if (figure->blocks[i][j] != 0) {
        int fx = figure->x + j;
        int fy = figure->y + i;
        field[fy][fx] = figure->blocks[i][j];
      }
    }
  }
}

int fullLine(int line) {
  Game_t* game = gameT();
  int** field = game->game_info->field;

  for (int i = 0; i < MAP_WIDTH; i++) {
    if (field[line][i] == 0) {
      return 0;
    }
  }

  return 1;
}

void dropLine(int line) {
  Game_t* game = gameT();
  int** field = game->game_info->field;
  if (line == 0) {
    for (int j = 0; j < MAP_WIDTH; j++) {
      field[line][j] = 0;
    }
  } else {
    for (int i = line; i > 0; i--) {
      for (int j = 0; j < MAP_WIDTH; j++) {
        field[i][j] = field[i - 1][j];
      }
    }
  }
}

void eraseLine() {
  Game_t* game = gameT();
  int count = 0;
  for (int i = MAP_HEIGHT - 1; i >= 0; i--) {
    while (fullLine(i)) {
      dropLine(i);
      count++;
    }
  }

  game->game_info->score += scoring(count);
  increaseLevel();
}

int scoring(int lines) {
  int score = 0;
  switch (lines) {
    case 1:
      score = 100;
      break;

    case 2:
      score = 300;
      break;

    case 3:
      score = 700;
      break;

    case 4:
      score = 1500;
      break;

    default:
      break;
  }

  return score;
}

void increaseLevel() {
  Game_t* game = gameT();
  if (game->game_info->level < MAX_LEVELS) {
    game->game_info->level = game->game_info->score / LEVEL_THRESHOLD + 1;
    if (game->game_info->level > MAX_LEVELS) {
      game->game_info->level = MAX_LEVELS;
    }

    game->game_info->speed = game->game_info->level;
  }
}

void createHighScore() {
  FILE* fp;
  if ((fp = fopen(TETRIS_HIGH_SCORE_FILE, "w")) == NULL) {
    printf("Error opening file!\n");
    exit(1);
  } else {
    fprintf(fp, "%d", 0);
    fclose(fp);
  }
}

int getHighScore() {
  FILE* fp;
  if ((fp = fopen(TETRIS_HIGH_SCORE_FILE, "r")) == NULL) {
    createHighScore();
    return 0;
  } else {
    int score;
    fscanf(fp, "%d", &score);
    fclose(fp);
    return score;
  }
}

void setHighScore() {
  Game_t* game = gameT();
  FILE* fp;
  if ((fp = fopen(TETRIS_HIGH_SCORE_FILE, "w")) == NULL) {
    printf("Error opening file!\n");
    exit(1);
  } else {
    fprintf(fp, "%d", game->game_info->score);
    fclose(fp);
  }
}