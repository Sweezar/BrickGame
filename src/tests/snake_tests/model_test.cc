#include "tests.h"

using namespace std;
using namespace s21;

TEST(TestModel, Constructor) {
  // Arrange
  Model model;

  // Act
  GameInfo_t info = model.getInfo();

  // Assert
  ASSERT_NE(info.field, nullptr);
  ASSERT_EQ(info.level, 1);
  ASSERT_EQ(info.pause, GAMESTART);
}

TEST(TestModel, StartGame) {
  // Arrange
  Model model;

  // Act
  model.startGame();
  GameInfo_t info = model.getInfo();

  // Assert
  ASSERT_EQ(info.pause, UNPAUSE);
}

TEST(TestModel, ChangeDirectionLeft_1) {
  // Arrange
  Model model;

  // Act
  model.changeDirectionDown();
  model.changeDirectionLeft();
  Direction dir = model.getDirection();

  // Assert
  ASSERT_EQ(dir, LEFT_DIR);
}

TEST(TestModel, ChangeDirectionLeft_2) {
  // Arrange
  Model model;

  // Act
  model.changeDirectionDown();
  model.changeDirectionRight();
  model.changeDirectionLeft();
  Direction dir = model.getDirection();

  // Assert
  ASSERT_EQ(dir, RIGHT_DIR);
}

TEST(TestModel, ChangeDirectionRight_1) {
  // Arrange
  Model model;

  // Act
  model.changeDirectionDown();
  model.changeDirectionRight();
  Direction dir = model.getDirection();

  // Assert
  ASSERT_EQ(dir, RIGHT_DIR);
}

TEST(TestModel, ChangeDirectionRight_2) {
  // Arrange
  Model model;

  // Act
  model.changeDirectionRight();
  Direction dir = model.getDirection();

  // Assert
  ASSERT_EQ(dir, LEFT_DIR);
}

TEST(TestModel, ChangeDirectionDown_1) {
  // Arrange
  Model model;

  // Act
  model.changeDirectionDown();
  Direction dir = model.getDirection();

  // Assert
  ASSERT_EQ(dir, DOWN_DIR);
}

TEST(TestModel, ChangeDirectionDown_2) {
  // Arrange
  Model model;

  // Act
  model.changeDirectionUp();
  Direction dir = model.getDirection();

  // Assert
  ASSERT_EQ(dir, UP_DIR);
}

TEST(TestModel, ChangeDirectionUp_1) {
  // Arrange
  Model model;

  // Act
  model.changeDirectionUp();
  Direction dir = model.getDirection();

  // Assert
  ASSERT_EQ(dir, UP_DIR);
}

TEST(TestModel, ChangeDirectionUp_2) {
  // Arrange
  Model model;

  // Act
  model.changeDirectionDown();
  model.changeDirectionUp();
  Direction dir = model.getDirection();

  // Assert
  ASSERT_EQ(dir, DOWN_DIR);
}

TEST(TestModel, MoveSnakeForward_1) {
  // Arrange
  Model model;
  Snake_t snake_1;
  Snake_t snake_2;

  // Act
  snake_1 = model.getSnake();
  model.pauseGame();
  model.moveSnakeForward();
  snake_2 = model.getSnake();

  // Assert
  ASSERT_EQ(snake_1, snake_2);
}

TEST(TestModel, MoveSnakeForward_2) {
  // Arrange
  Model model;
  Snake_t snake_1;
  Snake_t snake_2;

  // Act
  model.startGame();
  snake_1 = model.getSnake();
  model.moveSnakeForward();
  snake_2 = model.getSnake();

  // Assert
  ASSERT_NE(snake_1, snake_2);
}

TEST(TestModel, Shifting_1) {
  // Arrange
  Model model;
  Snake_t snake_1;
  Snake_t snake_2;

  // Act
  model.startGame();
  model.setState(SHIFTING);
  snake_1 = model.getSnake();
  model.shifting();
  snake_2 = model.getSnake();

  // Assert
  ASSERT_NE(snake_1, snake_2);
  ASSERT_EQ(model.getState(), MOVING);
}

TEST(TestModel, Shifting_2) {
  // Arrange
  Model model;
  Snake_t snake_1;
  Snake_t snake_2;

  // Act
  model.startGame();
  model.setState(MOVING);
  snake_1 = model.getSnake();
  model.shifting();
  snake_2 = model.getSnake();

  // Assert
  ASSERT_EQ(snake_1, snake_2);
  ASSERT_EQ(model.getState(), MOVING);
}

TEST(TestModel, PauseGame_1) {
  // Arrange
  Model model;

  // Act
  model.startGame();
  model.pauseGame();
  GameInfo_t info = model.getInfo();

  ASSERT_EQ(info.pause, PAUSE);
}

TEST(TestModel, PauseGame_2) {
  // Arrange
  Model model;

  // Act
  model.startGame();
  model.pauseGame();
  model.pauseGame();
  GameInfo_t info = model.getInfo();

  ASSERT_EQ(info.pause, UNPAUSE);
}

TEST(TestModel, EndGame) {
  // Arrange
  Model model;

  // Act
  model.startGame();
  model.endGame();
  GameInfo_t info = model.getInfo();

  // Assert
  ASSERT_EQ(model.getState(), ENDGAME);
  ASSERT_EQ(info.pause, GAMEOVER);
}

TEST(TestModel, Eating) {
  // Arrange
  Model model;
  Apple_t apple;
  Snake_t snake;

  // Act
  model.startGame();
  snake = model.getSnake();

  apple.position.x = snake.body[0].x - 1;
  apple.position.y = snake.body[0].y;

  model.setApple(apple);
  model.moveSnakeForward();
  model.moveSnakeForward();

  snake = model.getSnake();
  GameInfo_t info = model.getInfo();

  // Assert
  ASSERT_EQ(info.score, 1);
  ASSERT_NE(model.getApple(), apple);
}

TEST(TestModel, MoveLeft) {
  // Arrange
  Model model;
  Snake_t snake;

  // Act
  model.startGame();
  snake = model.getSnake();
  model.moveSnakeForward();

  // Assert
  ASSERT_NE(snake, model.getSnake());
}

TEST(TestModel, MoveUp) {
  // Arrange
  Model model;
  Snake_t snake;

  // Act
  model.startGame();
  snake = model.getSnake();
  model.changeDirectionUp();

  // Assert
  ASSERT_NE(snake, model.getSnake());
}

TEST(TestModel, MoveRight) {
  // Arrange
  Model model;
  Snake_t snake;

  // Act
  model.startGame();
  snake = model.getSnake();
  model.changeDirectionUp();
  model.changeDirectionRight();

  // Assert
  ASSERT_NE(snake, model.getSnake());
}

TEST(TestModel, MoveDown) {
  // Arrange
  Model model;
  Snake_t snake;

  // Act
  model.startGame();
  snake = model.getSnake();
  model.changeDirectionDown();

  // Assert
  ASSERT_NE(snake, model.getSnake());
}

TEST(TestModel, WinGame) {
  // Arrange
  Model model;
  Snake_t snake;
  Apple_t apple;

  // Act
  model.startGame();

  snake = model.getSnake();
  snake.length = MAX_SNAKE_LENGTH - 1;
  model.setSnake(snake);

  apple.position.x = snake.body[0].x - 1;
  apple.position.y = snake.body[0].y;
  model.setApple(apple);
  model.moveSnakeForward();

  // Assert
  ASSERT_EQ(model.getInfo().pause, GAMEWIN);
  ASSERT_EQ(model.getState(), ENDGAME);
}

TEST(TestModel, checkCollideField) {
  // Arrange
  Model model;
  Snake_t snake;

  // Act
  model.startGame();

  snake = model.getSnake();
  while (snake.body[0].x != 0) {
    model.moveSnakeForward();
    snake = model.getSnake();
  }
  model.moveSnakeForward();

  // Assert
  ASSERT_EQ(model.getState(), ENDGAME);
}

TEST(TestModel, checkCollideSnake) {
  // Arrange
  Model model;
  Snake_t snake;

  // Act
  model.startGame();

  snake = model.getSnake();
  snake.body.push_back(snake.body.back());
  snake.body.back().x++;
  model.setSnake(snake);

  model.changeDirectionUp();
  model.changeDirectionRight();
  model.changeDirectionDown();

  // Assert
  ASSERT_EQ(model.getState(), ENDGAME);
}