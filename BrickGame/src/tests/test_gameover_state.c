#include "tests.h"
START_TEST(test_1) {
  WIN_INIT(50);
  init_game_info();
  init_colors();
  next_brick = get_random_brick();
  activ_brick = next_brick;
  ck_assert_int_eq(START_state, gameover_state());
  init_game_info();

  game_info.score = game_info.high_score + 1000;
  ck_assert_int_eq(START_state, gameover_state());
  endwin();
}

END_TEST
Suite *test_gameover_state(void) {
  Suite *s = suite_create(BLUE "test_gameover_state" NOCOLOR);
  TCase *tc = tcase_create("test_tc");
  suite_add_tcase(s, tc);
  tcase_add_test(tc, test_1);
  return s;
}
