#ifndef INPUT_H
#define INPUT_H

#include <stdbool.h>

#include "../../../brick_game/tetris/fsm.h"
#include "../../../brick_game/tetris/objects.h"
#include "../../../brick_game/tetris/tetris.h"
#include "./frontend.h"

#define TETRIS_GAME 1
#define SNAKE_GAME 2

UserAction_t getUserAction();
void userInput(UserAction_t user_action, bool hold);
int changeGame();

#endif