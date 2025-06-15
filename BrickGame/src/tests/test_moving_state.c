#include "tests.h"
START_TEST(test_1) {
  WIN_INIT(50);
  init_game_info();
  init_colors();
  time_update = clock() - 1990;
  game_info.level = 10;
  ck_assert_int_eq(FALLING_state, moving_state(Up));
  time_update = clock();
  ck_assert_int_eq(MOVING_state, moving_state(Up));
  time_update = clock();
  ck_assert_int_eq(MOVING_state, moving_state(Left));
  time_update = clock();
  ck_assert_int_eq(MOVING_state, moving_state(Right));
  time_update = clock();
  ck_assert_int_eq(MOVING_state, moving_state(Down));
  time_update = clock();
  ck_assert_int_eq(MOVING_state, moving_state(Action));
  time_update = clock();
  ck_assert_int_eq(MOVING_state, moving_state(Pause));
  time_update = clock();
  ck_assert_int_eq(MOVING_state, moving_state(Pause));
  activ_brick = &I;
  activ_brick->x = -2;
  activ_brick->y = 5;
  activ_brick->rotation = 1;
  time_update = clock();
  ck_assert_int_eq(MOVING_state, moving_state(Action));
  free_game_info();
  endwin();
}

END_TEST
Suite *test_moving_state(void) {
  Suite *s = suite_create(BLUE "test_moving_state" NOCOLOR);
  TCase *tc = tcase_create("test_tc");
  suite_add_tcase(s, tc);
  tcase_add_test(tc, test_1);
  return s;
}
