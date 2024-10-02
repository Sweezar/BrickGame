#ifndef TESTS_H_
#define TESTS_H_

#include <check.h>
#include <stdio.h>
#include <unistd.h>

#include "../../brick_game/tetris//fsm.h"
#include "../../brick_game/tetris/tetris.h"

Suite *test_tetris_function(void);
Suite *test_tetris_fsm(void);

#endif
