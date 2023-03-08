BUILD_DIR=build

all: clean test
.PHONY: all

rebuild: clean all
.PHONY: rebuild

clean:
	-rm -rf $(BUILD_DIR)
.PHONY: clean

test:
	cmake -S . -B $(BUILD_DIR) -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=TEST -DCMAKE_VERBOSE_MAKEFILE:BOOL=ON
	make -C $(BUILD_DIR) tests
	./$(BUILD_DIR)/tests
	geninfo $(shell find . -name '*.gcda' -or -name '*.gcno') . -o ./build/info
	genhtml ./build/info -o ./build/coverage
	open ./build/coverage/index.html
.PHONY: test

#s21_matrix_oop.a:
#	cmake -S . -B $(BUILD_DIR) -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=RELEASE -DCMAKE_VERBOSE_MAKEFILE:BOOL=ON
#	make -C $(BUILD_DIR) s21_matrix_oop
#.PHONY: s21_matrix_oop.a

#lint:
#	clang-format -n $(shell find . -name "*\.cpp" -or -name "*\.h")