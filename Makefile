# @file Makefile
# @author Lubrin, Clarence, U.
# @details Builds the emulator library, command-line executable, and tests.

CC ?= cc
CFLAGS ?= -std=c11 -Wall -Wextra -Wpedantic -I./src
LDFLAGS ?=

SRC := $(shell find src -name '*.c' -print)
OBJ := $(SRC:.c=.o)
TEST_SRC := $(shell find tests -maxdepth 1 -name '*.c' -print)

.PHONY: all clean test

all: i386_emulator

i386_emulator: $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(OBJ)

test: $(TEST_SRC) $(filter-out src/main.o,$(OBJ))
	@set -e; for test in $(TEST_SRC); do \
		name=$$(basename "$$test" .c); \
		$(CC) $(CFLAGS) -o "test_$$name" $(filter-out src/main.o,$(OBJ)) "$$test"; \
		"./test_$$name"; \
		rm -f "test_$$name"; \
	done

clean:
	rm -f $(OBJ) i386_emulator test_runner test_test_*
