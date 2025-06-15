#include "tests.h"
START_TEST(test_1) {
  WIN_INIT(50);
  init_game_info();
  init_colors();
  ck_assert_int_eq(SPAWN_state, start_state(Start));
  free_game_info();
  endwin();
}
START_TEST(test_2) {
  WIN_INIT(50);
  init_game_info();
  init_colors();
  ck_assert_int_eq(START_state, start_state(Up));
  free_game_info();
  endwin();
}
START_TEST(test_3) {}
START_TEST(test_4) {}
START_TEST(test_5) {}

END_TEST
Suite *test_start_state(void) {
  Suite *s = suite_create(BLUE "test_start_state" NOCOLOR);
  TCase *tc = tcase_create("test_tc");
  suite_add_tcase(s, tc);
  tcase_add_test(tc, test_1);
  tcase_add_test(tc, test_2);
  tcase_add_test(tc, test_3);
  tcase_add_test(tc, test_4);
  tcase_add_test(tc, test_5);
  return s;
}
