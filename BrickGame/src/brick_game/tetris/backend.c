#include "backend.h"

void game_loop(void) {
  rand();
  rand();
  init_colors();
  print_overlay();
  game_state state = START_state;
  int input;
  UserAction_t action = -1;
  init_game_info();
  while (action != Terminate) {
    input = GET_USER_INPUT;
    action = get_signal(input);
    switch (state) {
      case START_state:
        state = start_state(action);
        break;
      case SPAWN_state:
        state = spawn_state();
        break;
      case MOVING_state:
        state = moving_state(action);
        break;
      case FALLING_state:
        state = falling_state(action);
        break;
      case CONNECTED_state:
        state = connected_state();
        break;
      case GAMEOVER_state:
        state = gameover_state();
        init_game_info();
        break;
      default:
        break;
    }
    refresh();
  }
  free_game_info();
}
game_state start_state(UserAction_t action) {
  game_state rc = START_state;
  if (action == Start) {
    clear();
    game_info.pause = 0;
    next_brick = get_random_brick();
    set_brick_mass(next_brick->mass[0], game_info.next);
    print_stats(&game_info);
    print_overlay();
    rc = SPAWN_state;
  }
  return rc;
}
game_state spawn_state(void) {
  game_state rc = SPAWN_state;
  activ_brick = next_brick;
  activ_brick->rotation = 0;
  activ_brick->x = MAP_X / 2 - 2;
  activ_brick->y = 0;

  next_brick = get_random_brick();
  set_brick_mass(next_brick->mass[0], game_info.next);
  if (check_collisions()) {
    move_brick(Up);
    rc = GAMEOVER_state;
  } else {
    time_update = clock();
    rc = MOVING_state;
  }
  updateCurrentState();
  return rc;
}
game_state moving_state(UserAction_t action) {
  game_state rc = MOVING_state;

  if (game_info.pause == 0) {
    clock_t now = clock();
    double elapsed = (double)(now - time_update);
    if (elapsed > (1000.0 - (game_info.level * 50))) rc = FALLING_state;
    switch (action) {
      case Left:
      case Right:
      case Down:
        if (try_move_brick(action)) updateCurrentState();
        break;
      case Action:
        if (rotate_brick()) updateCurrentState();
        break;
      case Pause:
        game_info.pause = 1;
        print_pause();
        break;
      default:
        break;
    }
  } else if (action == Pause) {
    time_update = clock();
    game_info.pause = 0;
    print_stats(&game_info);
  }
  return rc;
}
game_state falling_state(UserAction_t action) {
  time_update = clock();
  game_state rc = MOVING_state;

  if (game_info.pause == 0) {
    switch (action) {
      case Left:
      case Right:
      case Down:
        try_move_brick(action);
        break;
      case Action:
        rotate_brick();
        break;
      case Pause:
        game_info.pause = 1;
        print_pause();
        break;
      default:
        break;
    }
  } else if (action == Pause)
    game_info.pause = 0;

  if (try_move_brick(Down) == 0) rc = CONNECTED_state;
  updateCurrentState();
  return rc;
}
game_state connected_state(void) {
  game_state rc = SPAWN_state;
  add_brick_on_board();
  int full_lines = clean_full_lines();
  if (full_lines == 1) game_info.score += 100;
  if (full_lines == 2) game_info.score += 300;
  if (full_lines == 3) game_info.score += 700;
  if (full_lines == 4) game_info.score += 1500;
  game_info.level = game_info.score / 600;
  if (game_info.level > MAX_LVL) game_info.level = MAX_LVL;
  print_board(&game_info);
  refresh();
  sleep(1);
  drop_lines(full_lines);
  print_board(&game_info);
  return rc;
}
int clean_full_lines(void) {
  int full_lines = 0;
  for (size_t i = 0; i < MAP_Y; i++) {
    int line = 0;
    for (size_t j = 0; j < MAP_X; j++)
      if (game_info.field[i][j] != 0) line++;

    if (line == MAP_X) {
      full_lines++;
      clean_line(i);
    }
  }

  return full_lines;
}
void clean_line(int index_line) {
  for (int j = 0; j < MAP_X; j++) game_info.field[index_line][j] = 0;
}
void drop_lines(int num_lines) {
  while (num_lines) {
    for (size_t i = MAP_Y - 1; i > 0 && num_lines; i--) {
      int emply_line = 0;
      for (size_t j = 0; j < MAP_X; j++)
        if (game_info.field[i][j] == 0) emply_line++;
      if (emply_line == MAP_X) {
        num_lines--;
        drop_line(i);
        i++;
      }
    }
  }
}
void drop_line(int index_line) {
  for (size_t i = index_line; i > 0; i--)
    for (size_t j = 0; j < MAP_X; j++)
      game_info.field[i][j] = game_info.field[i - 1][j];

  for (size_t i = 0; i < MAP_X; i++) game_info.field[0][i] = 0;
}
game_state gameover_state(void) {
  game_state rc = START_state;
  free_game_info();
  print_gameover();
  return rc;
}

GameInfo_t updateCurrentState(void) {
  print_stats(&game_info);
  return game_info;
}
int check_collisions(void) {
  int rc = 0;
  for (size_t i = 0; i < 4; i++)
    for (size_t j = 0; j < 4; j++) {
      if (activ_brick->mass[activ_brick->rotation][i][j] != 0) {
        int tmpX = activ_brick->x + j;
        int tmpY = activ_brick->y + i;
        if (tmpX < 0 || tmpX >= MAP_X || tmpY >= MAP_Y)
          rc += 1;
        else if (tmpY >= 0)
          if (game_info.field[tmpY][tmpX] != 0) rc += 1;
      }
    }
  return rc;
}
int rotate_brick(void) {
  int rc = 1;
  int start_rotation = activ_brick->rotation;
  activ_brick->rotation = (activ_brick->rotation + 1) % 4;
  if (check_collisions()) rc = try_wall_kick();
  if (rc == 0) activ_brick->rotation = start_rotation;
  return rc;
}
int try_wall_kick(void) {
  int rc = 1;
  if (check_collisions()) rc = 0;
  if (rc == 0)
    rc = try_move_brick(Left) || try_move_brick(Right) || try_move_brick(Up);
  if (rc == 0) {
    move_brick(Up);
    rc = try_move_brick(Left) || try_move_brick(Right) || try_move_brick(Up);
  }
  if (rc == 0) {
    move_brick(Up);
    rc = try_move_brick(Left) || try_move_brick(Right);
  }
  if (rc == 0) {
    move_brick(Down);
    move_brick(Down);
  }
  if (rc == 0 && activ_brick == &I && activ_brick->rotation % 2 == 0) {
    move_brick(Left);
    rc = try_move_brick(Left);
    if (rc == 0) {
      move_brick(Right);
      move_brick(Right);
      rc = try_move_brick(Right);
    }
    if (rc == 0) move_brick(Left);
  }
  return rc;
}
void move_brick(UserAction_t action) {
  switch (action) {
    case Up:
      activ_brick->y -= 1;
      break;
    case Left:
      activ_brick->x -= 1;
      break;
    case Right:
      activ_brick->x += 1;
      break;
    case Down:
      activ_brick->y += 1;
      break;
    default:
      break;
  }
}
int try_move_brick(UserAction_t action) {
  int rc = 1;
  move_brick(action);
  if (check_collisions()) {
    rc = 0;
    switch (action) {
      case Left:
        move_brick(Right);
        break;
      case Right:
        move_brick(Left);
        break;
      case Down:
        move_brick(Up);
        break;
      case Up:
        move_brick(Down);
        break;
      default:
        break;
    }
  }
  return rc;
}

void add_brick_on_board(void) {
  for (size_t i = 0; i < 4; i++) {
    if (activ_brick->y < 0 && i == 0) i = 1;
    for (size_t j = 0; j < 4; j++) {
      if (activ_brick->mass[activ_brick->rotation][i][j] != 0) {
        int tmpX = activ_brick->x + j;
        int tmpY = activ_brick->y + i;
        game_info.field[tmpY][tmpX] =
            activ_brick->mass[activ_brick->rotation][i][j];
      }
    }
  }
}
UserAction_t get_signal(int user_input) {
  UserAction_t rc = Up;

  if (user_input == 'S' || user_input == 's')
    rc = Start;
  else if (user_input == 'P' || user_input == 'p')
    rc = Pause;
  else if (user_input == KEY_LEFT)
    rc = Left;
  else if (user_input == KEY_RIGHT)
    rc = Right;
  else if (user_input == KEY_UP)
    rc = Up;
  else if (user_input == KEY_DOWN)
    rc = Down;
  else if (user_input == ' ')
    rc = Action;
  else if (user_input == 'Q' || user_input == 'q')
    rc = Terminate;
  return rc;
}
void init_game_info(void) {
  game_info.field = calloc(MAP_Y, sizeof(int *));
  for (size_t i = 0; i < MAP_Y; i++)
    game_info.field[i] = calloc(MAP_X, sizeof(int));

  game_info.next = calloc(4, sizeof(int *));
  for (size_t i = 0; i < 4; i++) game_info.next[i] = calloc(4, sizeof(int));

  game_info.score = 0;
  game_info.high_score = read_high_score();
  game_info.level = 0;
  game_info.speed = 0;
  game_info.pause = 0;
}
int read_high_score(void) {
  FILE *file = fopen("gui/cli/HI_score.txt", "r");
  if (file == NULL) return 0;

  int high_score = 0;
  fscanf(file, "%d", &high_score);
  fclose(file);
  return high_score;
}
void write_new_high_score(void) {
  FILE *file = fopen("gui/cli/HI_score.txt", "w");
  fprintf(file, "%d", game_info.score);
  fclose(file);
}
void free_game_info(void) {
  for (size_t i = 0; i < MAP_Y; i++) free(game_info.field[i]);
  free(game_info.field);

  for (size_t i = 0; i < 4; i++) free(game_info.next[i]);
  free(game_info.next);
}

void print_brick_on_board(void) {
  for (size_t i = 0; i < 4 && activ_brick != NULL; i++) {
    for (size_t j = 0; j < 4; j++) {
      if (activ_brick->mass[activ_brick->rotation][i][j] != 0) {
        attron(COLOR_PAIR(activ_brick->mass[activ_brick->rotation][i][j]));
        MVPRINTW(activ_brick->y + i + 1,
                 (activ_brick->x + j) * PIXEL_SIZE_HORIZONTAL + 1, "[]");
        attroff(COLOR_PAIR(activ_brick->mass[activ_brick->rotation][i][j]));
      }
    }
  }
}
