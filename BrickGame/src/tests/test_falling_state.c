#include "tests.h"
START_TEST(test_1) {
  WIN_INIT(50);
  init_game_info();
  init_colors();
  next_brick = get_random_brick();
  activ_brick = next_brick;
  ck_assert_int_eq(MOVING_state, falling_state(Left));
  ck_assert_int_eq(MOVING_state, falling_state(Right));
  ck_assert_int_eq(MOVING_state, falling_state(Down));
  ck_assert_int_eq(MOVING_state, falling_state(Left));
  ck_assert_int_eq(MOVING_state, falling_state(Action));
  ck_assert_int_eq(MOVING_state, falling_state(Pause));
  for (size_t i = 0; i < MAP_Y; i++) {
    for (size_t j = 0; j < MAP_X; j++) {
      game_info.field[i][j] = 1;
    }
  }

  ck_assert_int_eq(CONNECTED_state, falling_state(Up));
  ck_assert_int_eq(CONNECTED_state, falling_state(Left));
  ck_assert_int_eq(CONNECTED_state, falling_state(Right));
  ck_assert_int_eq(CONNECTED_state, falling_state(Down));
  ck_assert_int_eq(CONNECTED_state, falling_state(Action));
  ck_assert_int_eq(CONNECTED_state, falling_state(Pause));
  free_game_info();
  endwin();
}

END_TEST
Suite *test_falling_state(void) {
  Suite *s = suite_create(BLUE "test_falling_state" NOCOLOR);
  TCase *tc = tcase_create("test_tc");
  suite_add_tcase(s, tc);
  tcase_add_test(tc, test_1);
  return s;
}
