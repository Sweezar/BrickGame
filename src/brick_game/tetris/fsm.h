#ifndef FSM_H_
#define FSM_H_

#include "objects.h"
#include "tetris.h"

Signals getSignal(int user_input);
void tetrisTimer();
void exitstate();
void spawn();
void movedown();
void moveright();
void moveleft();
void rotate();
void shift();
void gamepause();
void plant();
void startstate();
action fsm(Tetris_states state, UserAction_t user_action);

#endif  // FSM_H_
