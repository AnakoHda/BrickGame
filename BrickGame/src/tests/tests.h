#include <check.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#include "../brick_game/tetris/backend.h"
#include "../brick_game/tetris/objects.h"
#include "../gui/cli/frontend.h"

#define RED "\033[31m"
#define GREEN "\033[32m"
#define NOCOLOR "\033[0m"
#define BLUE "\033[34m"

Suite* test_start_state(void);
Suite* test_spawn_state(void);
Suite* test_moving_state(void);
Suite* test_falling_state(void);
Suite* test_connected_state(void);
Suite* test_gameover_state(void);
Suite* test_game_loop(void);
