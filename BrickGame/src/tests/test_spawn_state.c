#include "tests.h"
START_TEST(test_1) {
  setlocale(LC_ALL, "");
  WIN_INIT(50);
  init_colors();
  init_game_info();
  ck_assert_int_eq(MOVING_state, spawn_state());
  for (size_t i = 0; i < MAP_X; i++) {
    game_info.field[0][i] = 1;
    game_info.field[1][i] = 1;
  }
  next_brick = get_random_brick();
  activ_brick = next_brick;

  ck_assert_int_eq(GAMEOVER_state, spawn_state());
  free_game_info();
  endwin();
}

END_TEST
Suite *test_spawn_state(void) {
  Suite *s = suite_create(BLUE "test_spawn_state" NOCOLOR);
  TCase *tc = tcase_create("test_tc");
  suite_add_tcase(s, tc);
  tcase_add_test(tc, test_1);
  return s;
}
