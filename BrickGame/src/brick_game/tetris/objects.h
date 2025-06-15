#include <locale.h>
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#ifndef OBJECTS_H
#define OBJECTS_H

typedef enum {
  Start,
  Pause,
  /// @brief клавиша завершения игры (мгновенного выхода)
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action
} UserAction_t;

typedef struct {
  /// @brief Игровое поле
  int **field;
  /// @brief Отображаемый слебующий brick
  int **next;
  int score;
  int high_score;
  int level;
  int speed;
  /// @brief состояние паузы: 1 - игра, 0 - пауза
  int pause;
} GameInfo_t;
/// @brief переменная инициализируемая при запуске игры, отображает текущее
/// состояние
extern GameInfo_t game_info;

typedef enum {
  START_state = 0,
  SPAWN_state,
  MOVING_state,
  FALLING_state,
  CONNECTED_state,
  GAMEOVER_state
} game_state;

typedef struct {
  /// @brief переменная со всеми возможными состояниями первый [] - поворот,
  /// второй [] - строки, третий [] - столбцы
  int mass[4][4][4];
  int x;
  int y;
  int rotation;
} brick;
/// @brief объявление всех brick
extern brick I, O, T, S, Z, L, J;
/// @brief ссылки на следующий brick
extern brick *next_brick;
/// @brief ссылка на активный brick
extern brick *activ_brick;
/// @brief массив всех brick
extern brick *all_bricks[7];
/// @brief переменная для хранения времения последнего обновления активного
/// brick
extern clock_t time_update;
#endif
