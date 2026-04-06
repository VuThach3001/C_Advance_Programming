CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -lm
TARGET_MAIN = solution
TARGET_TEST = test_suite

# Source files
MAIN_SRC = main.c
TEST_SRC = test.c

# Object files
MAIN_OBJ = main.o
TEST_OBJ = test.o

.PHONY: all clean run test help

help:
	@echo "Available targets:"
	@echo "  make test    - Compile and run the test suite"
	@echo "  make clean   - Remove compiled files"
	@echo "  make help    - Show this help message"

all: $(TARGET_TEST)

$(TARGET_TEST): $(MAIN_OBJ) $(TEST_OBJ)
	$(CC) $(CFLAGS) -o $(TARGET_TEST) $(MAIN_OBJ) $(TEST_OBJ)

$(MAIN_OBJ): $(MAIN_SRC)
	$(CC) $(CFLAGS) -c $(MAIN_SRC) -o $(MAIN_OBJ)

$(TEST_OBJ): $(TEST_SRC)
	$(CC) $(CFLAGS) -c $(TEST_SRC) -o $(TEST_OBJ)

test: $(TARGET_TEST)
	./$(TARGET_TEST)

clean:
	rm -f $(MAIN_OBJ) $(TEST_OBJ) $(TARGET_TEST) *.o
