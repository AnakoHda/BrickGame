// #include "../../gui/cli/frontend.h"
#include "backend.h"
int main(void) {
  setlocale(LC_ALL, "");
  WIN_INIT(50);
  srand(time(NULL));

  game_loop();

  // free_game_info();
  endwin();
  return 0;
}
