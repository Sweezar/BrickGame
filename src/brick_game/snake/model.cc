#include "model.h"

namespace s21 {
Model::Model() { init(); }

Model::~Model() { deleteField(); }

GameInfo_t Model::getInfo() {
  updateGameField();
  return this->_gameinfo;
}

Direction Model::getDirection() { return _snake.direction; }

Apple_t Model::getApple() { return _apple; }

Snake_t Model::getSnake() { return _snake; }

GameState Model::getState() { return _state; }

void Model::setState(GameState state) { this->_state = state; }

void Model::setApple(Apple_t apple) { this->_apple = apple; }

void Model::setSnake(Snake_t snake) { this->_snake = snake; }

void Model::startGame() {
  if (this->_state == GameState::STARTGAME) {
    this->_state = GameState::MOVING;
    this->_gameinfo.pause = UNPAUSE;
  }
}

void Model::changeDirectionLeft() {
  if (_gameinfo.pause != PAUSE) {
    if (_snake.direction != Direction::LEFT_DIR &&
        _snake.direction != Direction::RIGHT_DIR) {
      _snake.direction = Direction::LEFT_DIR;
      moveSnakeForward();
    }
  }
}
void Model::changeDirectionRight() {
  if (_gameinfo.pause != PAUSE) {
    if (_snake.direction != Direction::RIGHT_DIR &&
        _snake.direction != Direction::LEFT_DIR) {
      _snake.direction = Direction::RIGHT_DIR;
      moveSnakeForward();
    }
  }
}
void Model::changeDirectionUp() {
  if (_gameinfo.pause != PAUSE) {
    if (_snake.direction != Direction::UP_DIR &&
        _snake.direction != Direction::DOWN_DIR) {
      _snake.direction = Direction::UP_DIR;
      moveSnakeForward();
    }
  }
}

void Model::changeDirectionDown() {
  if (_gameinfo.pause != PAUSE) {
    if (_snake.direction != Direction::UP_DIR &&
        _snake.direction != Direction::DOWN_DIR) {
      _snake.direction = Direction::DOWN_DIR;
      moveSnakeForward();
    }
  }
}

void Model::moveSnakeForward() {
  if (_state == GameState::STARTGAME || _state == GameState::ENDGAME ||
      _gameinfo.pause == PAUSE) {
    return;
  }

  this->_start = clock();

  moveSnake();
}

void Model::shifting() {
  if (_state == SHIFTING) {
    moveSnakeForward();
    _state = GameState::MOVING;
  }
}

void Model::pauseGame() {
  if (this->_gameinfo.pause) {
    this->_start = clock();
    this->_gameinfo.pause = UNPAUSE;
  } else {
    this->_gameinfo.pause = PAUSE;
  }
}

void Model::endGame() {
  this->_state = GameState::ENDGAME;
  this->_gameinfo.pause = GAMEOVER;
  setHighScore();
}

void Model::init() {
  srand(time(NULL));
  initField();
  initGameInfo();
  initSnake();
  initApple();
  this->_state = GameState::STARTGAME;
  this->_start = 0;
}

void Model::initField() {
  this->_gameinfo.field = new int*[MAP_HEIGHT]();
  if (!this->_gameinfo.field) {
    throw std::bad_alloc();
  }

  for (int i = 0; i < MAP_HEIGHT; i++) {
    this->_gameinfo.field[i] = new int[MAP_WIDTH]();
    if (!this->_gameinfo.field[i]) {
      for (int j = 0; j < i; j++) {
        delete[] this->_gameinfo.field[j];
      }
      delete[] this->_gameinfo.field;
      throw std::bad_alloc();
    }
  }
}

void Model::deleteField() {
  for (int i = 0; i < MAP_HEIGHT; i++) {
    delete[] this->_gameinfo.field[i];
  }
  delete[] this->_gameinfo.field;
}

void Model::resetField() {
  for (int i = 0; i < MAP_HEIGHT; i++) {
    for (int j = 0; j < MAP_WIDTH; j++) {
      this->_gameinfo.field[i][j] = 0;
    }
  }
}

void Model::initGameInfo() {
  this->_gameinfo.score = 0;
  this->_gameinfo.level = 1;
  this->_gameinfo.speed = 1;
  this->_gameinfo.pause = GAMESTART;
  openHighScoreFile();
}

void Model::initApple() { generateApplePosition(); }

void Model::addApple() {
  this->_gameinfo.field[this->_apple.position.y][this->_apple.position.x] = 1;
}

void Model::generateApplePosition() {
  _apple.position.x = rand() % MAP_WIDTH;
  _apple.position.y = rand() % MAP_HEIGHT;
  if (checkAppleGeneration()) {
    generateApplePosition();
  }
}

bool Model::checkAppleGeneration() {
  for (auto n : this->_snake.body) {
    if (n == this->_apple.position) {
      return true;
    }
  }
  return false;
}

bool Model::checkEatApple() {
  if (_snake.body[0] == _apple.position) {
    _state = GameState::EATING;
    return true;
  }
  return false;
}

void Model::eatApple() {
  if (_state == GameState::EATING) {
    _snake.length++;
    increaseScore();
    if (this->_gameinfo.score % SCORE_FOR_LEVEL_UP == 0) {
      increaseLevel();
      increaseSpeed();
    }
    generateApplePosition();
    if (this->_gameinfo.score >= this->_gameinfo.high_score) {
      this->_gameinfo.high_score = this->_gameinfo.score;
    }
  }
  _state = GameState::MOVING;
  checkWin();
}

void Model::initSnake() {
  this->_snake.direction = Direction::LEFT_DIR;
  this->_snake.body = {{4, 10}, {5, 10}, {6, 10}, {7, 10}};
  this->_snake.length = 4;
}

void Model::addSnake() {
  for (auto n : this->_snake.body) {
    this->_gameinfo.field[n.y][n.x] = 1;
  }
}

void Model::shiftSnakePoints(Point_t point) {
  _snake.body.insert(_snake.body.begin(), point);
  if (point != _apple.position) {
    _snake.body.pop_back();
  }
}

bool Model::checkCollideField(Point_t point) {
  if (point.x < 0 || point.x >= MAP_WIDTH || point.y < 0 ||
      point.y >= MAP_HEIGHT) {
    return true;
  }
  return false;
}
bool Model::checkCollideSnake(Point_t point) {
  for (auto n : this->_snake.body) {
    if (point == n) {
      return true;
    }
  }
  return false;
}

bool Model::collide(Point_t point) {
  if (checkCollideField(point) || checkCollideSnake(point)) {
    _state = GameState::COLLISION;
    return true;
  }

  return false;
}

void Model::moveSnake() {
  Point_t newHead = _snake.body[0];
  switch (_snake.direction) {
    case Direction::UP_DIR:
      newHead.y--;
      break;

    case Direction::DOWN_DIR:
      newHead.y++;
      break;

    case Direction::LEFT_DIR:
      newHead.x--;
      break;

    case Direction::RIGHT_DIR:
      newHead.x++;
      break;
  }
  updateNewPoint(newHead);
}

void Model::timer() {
  if (_state == MOVING) {
    clock_t current_time = clock();
    double elapsed_time = ((double)(current_time - this->_start)) /
                          CLOCKS_PER_SEC * SNAKE_GAME_SPEED;
    double moving_time = SNAKE_GAME_SPEED / (this->_gameinfo.speed * 0.5);
    if (elapsed_time > moving_time) {
      this->_start = current_time;
      this->_state = SHIFTING;
    }
  }
}

void Model::increaseScore() { this->_gameinfo.score++; }

void Model::increaseLevel() {
  if (this->_gameinfo.level < MAX_GAME_LEVEL) {
    this->_gameinfo.level++;
  }
}

void Model::increaseSpeed() {
  if (this->_gameinfo.speed < MAX_GAME_SPEED) {
    this->_gameinfo.speed++;
  }
}

void Model::updateGameField() {
  timer();
  resetField();
  addApple();
  addSnake();
}

void Model::updateNewPoint(Point_t point) {
  if (!collide(point)) {
    shiftSnakePoints(point);
  } else {
    endGame();
  }
  if (checkEatApple()) {
    eatApple();
  }
}

void Model::checkWin() {
  if (_snake.length >= MAX_SNAKE_LENGTH) {
    _state = GameState::ENDGAME;
    _gameinfo.pause = GAMEWIN;
  }
}
void Model::openHighScoreFile() {
  std::ifstream _highscorefile(SNAKE_HIGH_SCORE_FILE);
  int score = 0;
  if (_highscorefile.is_open()) {
    _highscorefile >> score;
  }
  this->_gameinfo.high_score = score;

  _highscorefile.close();
}
void Model::setHighScore() {
  std::ofstream _highscorefile(SNAKE_HIGH_SCORE_FILE);
  _highscorefile << this->_gameinfo.high_score;
  _highscorefile.close();
}
}  // namespace s21
