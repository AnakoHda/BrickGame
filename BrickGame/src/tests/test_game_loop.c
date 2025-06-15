#include "tests.h"

START_TEST(test_1) {
  WIN_INIT(50);
  init_game_info();
  init_colors();
  UserAction_t action = Terminate;
  ungetch('q');
  ungetch('q');
  ungetch('q');
  ungetch('q');
  ungetch('q');
  game_loop();
  endwin();
}

END_TEST
Suite *test_game_loop(void) {
  Suite *s = suite_create(BLUE "test_game_loop" NOCOLOR);
  TCase *tc = tcase_create("test_tc");
  suite_add_tcase(s, tc);
  tcase_add_test(tc, test_1);
  return s;
}
