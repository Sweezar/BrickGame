#include "tests.h"

using namespace std;
using namespace s21;

TEST(TestController, Constructor) {
  // Arrange
  Model model;
  Controller controller(&model);

  // Act
  GameInfo_t info = controller.getGameInfo();

  // Assert
  ASSERT_NE(info.field, nullptr);
  ASSERT_EQ(info.level, 1);
  ASSERT_EQ(info.pause, GAMESTART);
}

TEST(TestController, StartGame) {
  // Arrange
  Model model;
  Controller controller(&model);

  // Act
  controller.startGame();
  GameInfo_t info = controller.getGameInfo();

  // Assert
  ASSERT_EQ(info.pause, UNPAUSE);
}

TEST(TestController, PauseGame_1) {
  // Arrange
  Model model;
  Controller controller(&model);

  // Act
  controller.startGame();
  controller.pauseGame();
  GameInfo_t info = controller.getGameInfo();

  // Assert
  ASSERT_EQ(info.pause, PAUSE);
}

TEST(TestController, PauseGame_2) {
  // Arrange
  Model model;
  Controller controller(&model);

  // Act
  controller.startGame();
  controller.pauseGame();
  controller.pauseGame();
  GameInfo_t info = controller.getGameInfo();

  // Assert
  ASSERT_EQ(info.pause, UNPAUSE);
}

TEST(TestController, TerminateGame) {
  // Arrange
  Model model;
  Controller controller(&model);

  // Act
  controller.startGame();
  controller.terminateGame();
  GameInfo_t info = controller.getGameInfo();

  // Assert
  ASSERT_EQ(info.pause, GAMEOVER);
}

TEST(TestController, Left) {
  // Arrange
  Model model;
  Controller controller(&model);
  Snake_t snake_1 = model.getSnake();
  Snake_t snake_2;

  // Act
  controller.startGame();
  controller.up();
  controller.left();
  snake_2 = model.getSnake();

  // Assert
  ASSERT_EQ(snake_1.body[0].x - 1, snake_2.body[0].x);
}

TEST(TestController, Right) {
  // Arrange
  Model model;
  Controller controller(&model);
  Snake_t snake_1 = model.getSnake();
  Snake_t snake_2;

  // Act
  controller.startGame();
  controller.up();
  controller.right();
  snake_2 = model.getSnake();

  // Assert
  ASSERT_EQ(snake_1.body[0].x + 1, snake_2.body[0].x);
}

TEST(TestController, Up) {
  // Arrange
  Model model;
  Controller controller(&model);
  Snake_t snake_1 = model.getSnake();
  Snake_t snake_2;

  // Act
  controller.startGame();
  controller.up();
  controller.right();
  snake_2 = model.getSnake();

  // Assert
  ASSERT_EQ(snake_1.body[0].y - 1, snake_2.body[0].y);
}

TEST(TestController, Down) {
  // Arrange
  Model model;
  Controller controller(&model);
  Snake_t snake_1 = model.getSnake();
  Snake_t snake_2;

  // Act
  controller.startGame();
  controller.down();
  snake_2 = model.getSnake();

  // Assert
  ASSERT_EQ(snake_1.body[0].y + 1, snake_2.body[0].y);
}

TEST(TestController, Action) {
  // Arrange
  Model model;
  Controller controller(&model);
  Snake_t snake_1 = model.getSnake();
  Snake_t snake_2;

  // Act
  controller.startGame();
  controller.action();
  snake_2 = model.getSnake();

  // Assert
  ASSERT_EQ(snake_1.body[0].x - 1, snake_2.body[0].x);
}

TEST(TestController, NoAction_1) {
  // Arrange
  Model model;
  Controller controller(&model);
  Snake_t snake_1 = model.getSnake();
  Snake_t snake_2;

  // Act
  controller.startGame();
  controller.noAction();
  snake_2 = model.getSnake();

  // Assert
  ASSERT_EQ(snake_1.body[0].x, snake_2.body[0].x);
}

TEST(TestController, NoAction_2) {
  // Arrange
  Model model;
  Controller controller(&model);
  Snake_t snake_1 = model.getSnake();
  Snake_t snake_2;

  // Act
  controller.startGame();
  model.setState(SHIFTING);
  controller.noAction();
  snake_2 = model.getSnake();

  // Assert
  ASSERT_EQ(snake_1.body[0].x - 1, snake_2.body[0].x);
}

TEST(TestController, Getters) {
  // Arrange
  Model model;
  Controller controller(&model);

  // Act
  controller.startGame();
  model.setState(SHIFTING);

  // Assert
  ASSERT_EQ(controller.getState(), model.getState());
  ASSERT_EQ(controller.getApple(), model.getApple());
}