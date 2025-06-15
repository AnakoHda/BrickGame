
#include "../../brick_game/tetris/objects.h"

#define MVPRINTW(y, x, ...) mvprintw(+(y), +(x), __VA_ARGS__)
#define MVADDCH(y, x, c) mvaddch(+(y), +(x), c)

#define COLOR_PINK 212
#define COLOR_ORANGE 208
#define PIXEL_SIZE_HORIZONTAL 2

#define MAP_X 10
#define MAP_Y 20
#define SUB_MAP_X 12
#define SUB_MAP_Y 20

#define main_board 0, MAP_Y + 1, 0, MAP_X *PIXEL_SIZE_HORIZONTAL + 1
#define sup_board                                     \
  0, SUB_MAP_Y + 1, MAP_X *PIXEL_SIZE_HORIZONTAL + 2, \
      MAP_X *PIXEL_SIZE_HORIZONTAL + 2 + SUB_MAP_X + 1
#define next_board                        \
  2, 7, MAP_X *PIXEL_SIZE_HORIZONTAL + 3, \
      MAP_X *PIXEL_SIZE_HORIZONTAL + 2 + SUB_MAP_X
#define Hi_scote_board                     \
  9, 11, MAP_X *PIXEL_SIZE_HORIZONTAL + 3, \
      MAP_X *PIXEL_SIZE_HORIZONTAL + 2 + SUB_MAP_X
#define scire_board                         \
  13, 15, MAP_X *PIXEL_SIZE_HORIZONTAL + 3, \
      MAP_X *PIXEL_SIZE_HORIZONTAL + 2 + SUB_MAP_X
#define lvl_board                           \
  17, 19, MAP_X *PIXEL_SIZE_HORIZONTAL + 3, \
      MAP_X *PIXEL_SIZE_HORIZONTAL + 2 + SUB_MAP_X
/// @brief  Функция инициализации пар цветов ncurses (front and back colors)
/// @param
void init_colors(void);
/// @brief функция отрисовки интерфейса (рамки, текст)
/// @param
void print_overlay(void);
/// @brief  отрисовка прямоугольника
/// @param top_y  верхняя точка
/// @param bottom_y нижняя точка
/// @param left_x левая
/// @param right_x правая
void print_rectangle(int top_y, int bottom_y, int left_x, int right_x);
/// @brief функция заполнения overlay данными из stats и отрисовки кубика поверх
/// игрового поля
/// @param stats структурв game_info хранящая актуальные данные игры
void print_stats(GameInfo_t *stats);
/// @brief заполняет окно next_brick данными из stats
/// @param stats структурв game_info хранящая актуальные данные игры
void print_next_brick(GameInfo_t *stats);
/// @brief заполняет основное игровое поле
/// @param game структурв game_info хранящая актуальные данные игры
void print_board(GameInfo_t *game);
/// @brief функция перезаписи поля из sourse в target
/// @param sourse откуда
/// @param target куда
void set_brick_mass(int sourse[4][4], int **target);
/// @brief отрисовка состояния паузы
/// @param
void print_pause(void);
/// @brief функция отрисовки сообщения об окончании игры и записи нового
/// HI_SCORE в файл
/// @param
void print_gameover(void);
/// @brief функция получения случайного кубика из массива all_bricks и
/// инициализирует его позицию по центру сверху
/// @param
/// @return возвращает указатель на случайный кубик
brick *get_random_brick(void);
/// @brief функция чтения HI_SCORE из файла, если не получилось найти файл
/// возвращает 0
/// @param
/// @return возвращает HI_SCORE
int read_high_score(void);
/// @brief функция записи HI_SCORE в файл из game_info
/// @param
void write_new_high_score(void);
/// @brief функция отрисовки кубика поверх игрового поля
/// @param
void print_brick_on_board(void);
