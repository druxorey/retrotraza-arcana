CC=g++
CFLAGS=-Wall
BUILD_DIR = build
SRC = main.cpp
OBJ = $(BUILD_DIR)/main.o

run: $(BUILD_DIR)/undercover
	$(BUILD_DIR)/undercover

compile: $(BUILD_DIR) $(OBJ)
	$(CC) -o $(BUILD_DIR)/undercover $(OBJ)

$(BUILD_DIR):
	mkdir -p $@

$(OBJ): $(SRC)
	$(CC) $(CFLAGS) -c $< -o $@

clear:
	rm -f $(BUILD_DIR)/*.o $(BUILD_DIR)/undercover

all: clear compile run
