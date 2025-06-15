#include "frontend.h"

void print_overlay(void) {
  print_rectangle(main_board);
  print_rectangle(sup_board);
  print_rectangle(next_board);
  print_rectangle(Hi_scote_board);
  print_rectangle(scire_board);
  print_rectangle(lvl_board);

  MVPRINTW(1, 24, "NEXT");
  MVPRINTW(8, 24, "Hi SCORE");
  MVPRINTW(12, 24, "Your SCORE");
  MVPRINTW(16, 24, "LVL");

  MVPRINTW(MAP_Y / 2 - 1, MAP_X * PIXEL_SIZE_HORIZONTAL / 2 - 5, "Press S");
  MVPRINTW(MAP_Y / 2, MAP_X * PIXEL_SIZE_HORIZONTAL / 2 - 5, " to start !");
}

void print_rectangle(int top_y, int bottom_y, int left_x, int right_x) {
  MVADDCH(top_y, left_x, ACS_ULCORNER);

  int i = left_x + 1;

  for (; i < right_x; i++) MVADDCH(top_y, i, ACS_HLINE);
  MVADDCH(top_y, i, ACS_URCORNER);

  for (int i = top_y + 1; i < bottom_y; i++) {
    MVADDCH(i, left_x, ACS_VLINE);
    MVADDCH(i, right_x, ACS_VLINE);
  }

  MVADDCH(bottom_y, left_x, ACS_LLCORNER);
  i = left_x + 1;
  for (; i < right_x; i++) MVADDCH(bottom_y, i, ACS_HLINE);
  MVADDCH(bottom_y, i, ACS_LRCORNER);
}
void init_colors(void) {
  start_color();
  use_default_colors();
  init_pair(1, COLOR_RED, -1);
  init_pair(208, COLOR_ORANGE, -1);
  init_pair(3, COLOR_YELLOW, -1);
  init_pair(212, COLOR_PINK, -1);
  init_pair(2, COLOR_GREEN, -1);
  init_pair(4, COLOR_BLUE, -1);
  init_pair(5, COLOR_MAGENTA, -1);
}
void set_brick_mass(int sourse[4][4], int **target) {
  for (size_t i = 0; i < 4; i++)
    for (size_t j = 0; j < 4; j++) target[i][j] = sourse[i][j];
}
void print_stats(GameInfo_t *stats) {
  print_board(stats);
  print_next_brick(stats);
  print_brick_on_board();
  MVPRINTW(10, 24, "%d", stats->high_score);
  MVPRINTW(14, 24, "%d", stats->score);
  MVPRINTW(18, 24, "%d", stats->level);

  if (stats->pause) print_pause();
}
void print_next_brick(GameInfo_t *stats) {
  for (size_t i = 0; i < 4; i++)
    for (size_t j = 0, k = 0; j < 4; j++, k += PIXEL_SIZE_HORIZONTAL)
      if (stats->next[i][j] != 0) {
        attron(COLOR_PAIR(stats->next[i][j]));
        MVPRINTW(3 + i, 25 + k, "[]");
        attroff(COLOR_PAIR(stats->next[i][j]));
      } else
        MVPRINTW(3 + i, 25 + k, "  ");
}
void print_board(GameInfo_t *stats) {
  for (int i = 0; i < MAP_Y; i++)
    for (int j = 0; j < MAP_X; j++)
      if (stats->field[i][j] != 0) {
        attron(COLOR_PAIR(stats->field[i][j]));
        MVPRINTW(i + 1, j * PIXEL_SIZE_HORIZONTAL + 1, "[]");
        attroff(COLOR_PAIR(stats->field[i][j]));
      } else
        MVPRINTW(i + 1, j * PIXEL_SIZE_HORIZONTAL + 1, "  ");
}
void print_gameover(void) {
  if (game_info.high_score < game_info.score) {
    MVPRINTW(MAP_Y / 2 - 1, MAP_X * PIXEL_SIZE_HORIZONTAL / 2 - 5,
             "NEW CSORE!!!");
    MVPRINTW(MAP_Y / 2, MAP_X * PIXEL_SIZE_HORIZONTAL / 2 - 5, "%d",
             game_info.score);
    write_new_high_score();
  } else {
    MVPRINTW(MAP_Y / 2 - 1, MAP_X * PIXEL_SIZE_HORIZONTAL / 2 - 5, "YOU LOST");
    MVPRINTW(MAP_Y / 2, MAP_X * PIXEL_SIZE_HORIZONTAL / 2 - 5, "your score:");
    MVPRINTW(MAP_Y / 2 + 1, MAP_X * PIXEL_SIZE_HORIZONTAL / 2 - 5, " %d",
             game_info.score);
    MVPRINTW(MAP_Y / 2 + 2, MAP_X * PIXEL_SIZE_HORIZONTAL / 2 - 5, "Start: S");
  }
}
brick *get_random_brick(void) {
  int num = rand() % 7;
  all_bricks[num]->x = MAP_X / 2 - 2;
  all_bricks[num]->y = 0;
  all_bricks[num]->rotation = 0;
  return all_bricks[num];
}

void print_pause(void) {
  MVPRINTW(MAP_Y / 2 - 1, MAP_X * PIXEL_SIZE_HORIZONTAL / 2 - 5, "Press P");
  MVPRINTW(MAP_Y / 2, MAP_X * PIXEL_SIZE_HORIZONTAL / 2 - 5, " to continue !");
}
