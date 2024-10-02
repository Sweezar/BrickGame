#ifndef TETRIS_H_
#define TETRIS_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "fsm.h"

int* chooseFigureTypes();
void freeFigureType(int* type);
int** createField();
void freeField(int** field);
Figure_t* createFigure();
void freeFigure(Figure_t* figure);
void createGame();
void freeGameInfo(GameInfo_t* info);
void freeGame();
Game_t* gameT();
void spawnFigure();
int collision();
void rotateFigure();
void plantFigure();
int fullLine(int line);
void dropLine(int line);
void eraseLine();
int scoring(int lines);
void increaseLevel();
void createHighScore();
int getHighScore();
void setHighScore();

#endif