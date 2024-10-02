#ifndef FRONTEND_H_
#define FRONTEND_H_

#include <ncurses.h>

#include "../../../brick_game/tetris/objects.h"
#include "../../../brick_game/tetris/tetris.h"

void initColors();
void printStartScreen();
void printFigure(Game_t* game, int i, int j, int* color);
void printField();

void printNextFigure();

void printInfo();

void printGame();
void printEndGame(GameInfo_t* game);

#endif