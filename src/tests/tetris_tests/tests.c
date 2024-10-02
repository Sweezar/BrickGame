#include "tests.h"

int main() {
  int failed = 0;

  Suite *tetris_test[] = {test_tetris_function(), test_tetris_fsm(), NULL};

  for (int i = 0; tetris_test[i] != NULL; i++) {
    SRunner *sr = srunner_create(tetris_test[i]);
    srunner_set_fork_status(sr, CK_NOFORK);
    srunner_run_all(sr, CK_NORMAL);
    failed += srunner_ntests_failed(sr);
    srunner_free(sr);
  }

  if (failed) {
    printf("\033[101m========== TESTS FAILED: %d ==========\033[0m\n", failed);
  } else {
    printf("\033[42m========== TESTS FAILED: %d ==========\033[0m\n", failed);
  }

  return 0;
}
