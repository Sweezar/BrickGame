#ifndef TERIS_GAME_H
#define TERIS_GAME_H

#include <stdio.h>
#include <stdlib.h>

#include "input.h"

GameInfo_t updateCurrentState();
void endGame(GameInfo_t* game);
void tetrisGame();

#endif