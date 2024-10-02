#include "controller.h"

GameState s21::Controller::getState() { return model->getState(); }

GameInfo_t s21::Controller::getGameInfo() { return model->getInfo(); }

void s21::Controller::startGame() { model->startGame(); }

void s21::Controller::pauseGame() { model->pauseGame(); }

void s21::Controller::terminateGame() { model->endGame(); }

void s21::Controller::left() { model->changeDirectionLeft(); }

void s21::Controller::right() { model->changeDirectionRight(); }

void s21::Controller::up() { model->changeDirectionUp(); }

void s21::Controller::down() { model->changeDirectionDown(); }

void s21::Controller::action() { model->moveSnakeForward(); }

void s21::Controller::noAction() { model->shifting(); }

Apple_t s21::Controller::getApple() { return model->getApple(); }
