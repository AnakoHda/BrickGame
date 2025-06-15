CC := gcc
CFLAGS := -I inc -std=c11 -Wall -Werror -Wextra -Wpedantic
BACK = brick_game/tetris/*.c
FRONT = gui/cli/*.c
MAIN = brick_game/tetris.c
SRC_TEST = ./tests/*.c

OS = $(shell uname)

ifeq ($(OS),Linux)
	CC += -DLINUX
	FLAGS_TEST = -lcheck -pthread -lsubunit -lm -lncurses
    OPEN = xdg-open
else ifeq ($(OS),Darwin)
	CC += -DDARWIN
	FLAGS_TEST = -lcheck -lncurses
	OPEN = open
endif

all: install dvi dist test gcov_report

install:
	@mkdir -p build
	@$(CC) $(CFLAGS) $(FRONT) $(BACK) -o build/tetris_game -lncurses

uninstall:
	- @rm -rf build 
clean: uninstall
	@rm -rf index.html
	@rm -rf dvi/html dvi/latex
	@rm -rf test
	@rm -rf tetris.tar.gz
	@rm -rf brick_game.a
	@rm -rf ./gcov_report ./report
dvi:
	@cd dvi && doxygen
dist:
	@mkdir -p dist
	@cp -r dvi dist
	@cp -r brick_game dist
	@cp -r gui dist
	@cp makefile dist
	@tar -czf tetris.tar.gz -C dist .
	@rm -rf dist
test: brick_game.a 
	@rm -rf	./$@
	$(CC)  -I inc -std=c11  $(SRC_TEST) ./brick_game.a $(FLAGS_TEST) -o ./test
gcov_report:
	@rm -rf ./$@ ./report
	@$(CC) -c $(FRONT) $(BACK) --coverage
	@ar rc ./libbrick_game.a ./*.o
	@ranlib ./libbrick_game.a
	@rm -rf ./*.o
	@$(CC) $(SRC_TEST) -L. -lbrick_game --coverage $(FLAGS_TEST) -o ./$@
	-@./$@ > /dev/null
	@mkdir report
	@lcov -q -t $@ -o $@.info -c -d .
	@genhtml -q $@.info -o report
	@rm -rf *.gcno *.gcda *.gcov *.info ./gcov_report ./libbrick_game.a
	
open:
	-@$(OPEN) "./report/index.html"
	-@$(OPEN) dvi/html/index.html
brick_game.a:
	@rm -rf ./$@
	$(CC) $(CFLAGS) -c $(FRONT) $(BACK)
	@ar rc ./$@ ./*.o
	@ranlib ./$@
	@rm -rf ./*.o
.PHONY: dvi clean install test gcov_report