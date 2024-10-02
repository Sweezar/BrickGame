# all, install, uninstall, clean, dvi, dist, test, gcov_report.
CSTD = -std=c11
CPPSTD = -std=c++17 -lstdc++
CFLAGS = -Wall -Wextra -Werror

TARGET := BrickGame

TETRIS_FILES = brick_game/tetris/*.c
TETRIS_HEADERS = brick_game/tetris/*.h
TETRIS_GUI_FILES = gui/cli/tetris/*.c
TETRIS_GUI_HEADERS = gui/cli/tetris/*.h
TETRIS_TEST_FILES = tests/tetris_tests/*.c
TETRIS_TEST_HEADERS = tests/tetris_tests/*.h

SNAKE_FILES = brick_game/snake/*.cc
SNAKE_HEADERS = brick_game/snake/*.h
SNAKE_GUI_FILES = gui/cli/snake/*.cc
SNAKE_GUI_HEADERS = gui/cli/snake/*.h
SNAKE_TEST_FILES = tests/snake_tests/*.cc
SNAKE_TEST_HEADERS = tests/snake_tests/*.h

ALL_FILES = $(TETRIS_FILES) $(TETRIS_HEADERS) $(TETRIS_GUI_FILES) $(TETRIS_GUI_HEADERS) $(TETRIS_TEST_FILES) $(TETRIS_TEST_HEADERS) $(SNAKE_FILES) $(SNAKE_HEADERS) $(SNAKE_GUI_FILES) $(SNAKE_GUI_HEADERS) $(SNAKE_TEST_FILES) $(SNAKE_TEST_HEADERS)

CONSOLE_MENU = gui/cli/main.cc
CMAKE_BUILD_DIR = gui/desktop/build

PARALLEL_JOBS = 8

GCOVFLAGS = -fprofile-arcs -ftest-coverage 
DIST_DIR = archive

.PHONY: test

UNAME_S = $(shell uname)

ifeq ($(UNAME_S),Darwin)
OPEN_CMD = open
ADD_LDFLAGS = -lgtest
endif

ifeq ($(UNAME_S),Linux)
OPEN_CMD = xdg-open
ADD_LDFLAGS = -lgtest -lm -lsubunit
endif

all: install

install: install_console install_desktop

install_console:
	@echo "Установка консольного приложения..."
	mkdir -p build
	g++ $(CFLAGS) $(CPPSTD) $(TETRIS_FILES) $(TETRIS_GUI_FILES) $(SNAKE_FILES) $(SNAKE_GUI_FILES) $(CONSOLE_MENU) $(ADD_LDFLAGS) -g -lncurses -o build/$(TARGET)_console
	@if [ -f "build/$(TARGET)_console" ]; then \
		echo "Установка build/$(TARGET)_console завершена"; \
	else \
		echo "Сборка завершилась с ошибкой"; exit 1; \
	fi

install_desktop:
	@echo "Установка десктопного приложения..."
	@mkdir -p $(CMAKE_BUILD_DIR)
	@cmake -B $(CMAKE_BUILD_DIR) -S gui/desktop || { echo "Ошибка CMake"; выход 1; }
	@cmake --build $(CMAKE_BUILD_DIR) --target $(TARGET) --parallel $(PARALLEL_JOBS) || { echo "Сборка завершилась с ошибкой"; exit 1; }
	@if [ -f "$(CMAKE_BUILD_DIR)/$(TARGET)" ]; then \
		echo "Копирование $(TARGET) в build/$(TARGET)_desktop"; \
		cp -R $(CMAKE_BUILD_DIR)/$(TARGET) build/$(TARGET)_desktop; \
		echo "Копирование $(TARGET) завершено"; \
	else \
		echo "Целевой объект $(TARGET) не найден в директории сборки."; \
		exit 1; \
	fi
	@rm -rf $(CMAKE_BUILD_DIR)

uninstall:
	rm -rf build

clean:
	rm -f tetris_test_file && rm -f *.txt
	rm -rf build
	rm -rf ${DIST_DIR}.tar.gz
	make clean_gcov
	rm -f test.info
	rm -f snake_test_file

dvi:
	$(OPEN_CMD) doc.html

dist:
	mkdir -p ${DIST_DIR}
	cp -rf brick_game/ ${DIST_DIR}/brick_game/
	cp -rf gui/ ${DIST_DIR}/gui/
	cp -rf Makefile ${DIST_DIR}/
	tar -czvf ${DIST_DIR}.tar.gz ${DIST_DIR}
	rm -rf ${DIST_DIR}

test: tetris_tests snake_tests

tetris_tests:
	gcc $(CFLAGS) $(CSTD) $(TETRIS_FILES) $(TETRIS_TEST_FILES) -o tetris_test_file -lcheck $(ADD_LDFLAGS) 
	./tetris_test_file

snake_tests:
	g++ $(CFLAGS) $(CPPSTD) $(SNAKE_FILES) $(SNAKE_TEST_FILES) -o snake_test_file -lgtest -pthread
	./snake_test_file

gcov_report: clean gcov_report_tetris gcov_report_snake

gcov_report_tetris:
	mkdir -p gcov
	gcc $(CFLAGS) $(CSTD) $(GCOVFLAGS) $(TETRIS_FILES) $(TETRIS_TEST_FILES) -o gcov_test -lcheck $(ADD_LDFLAGS)
	./gcov_test
	mv gcov_test *.gcno *.gcda ./gcov
	lcov --capture --directory ./gcov --output-file ./gcov/coverage.info
	genhtml -o ./gcov/report ./gcov/coverage.info
	$(OPEN_CMD) ./gcov/report/index.html

gcov_report_snake:
	@mkdir -p gcov
	g++ $(CFLAGS) $(CPPSTD) $(SNAKE_FILES) ${SNAKE_TEST_FILES} $(ADD_LDFLAGS) -pthread $(GCOVFLAGS) -o gcov_test
	./gcov_test
	lcov -t "test" -o test.info -c -d .
	lcov --remove test.info '/usr/*' -o test.info
	genhtml -o gcov test.info
	${OPEN_CMD} ./gcov/index.html

clang_format:
	cp ../materials/linters/.clang-format .
	clang-format -i $(ALL_FILES)
	rm -f .clang-format

clang_check:
	cp ../materials/linters/.clang-format .
	clang-format -n $(ALL_FILES)
	rm -f .clang-format

leaks_test: test
	leaks -atExit -- ./tetris_test_file
	leaks -atExit -- ./snake_test_file
	make clean

valgrind_test: test
	valgrind --leak-check=full ./tetris_test_file
	valgrind --leak-check=full ./snake_test_file
	make clean

clean_gcov:
	rm -rf gcov*