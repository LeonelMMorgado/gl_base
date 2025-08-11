CC = gcc

SRC_DIR = src
OBJ_DIR = build
INC_DIR = include
LIB_DIR = lib

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

FINAL = main

CFLAGS = -g -Wall -I$(INC_DIR) -Llib

ifeq ($(OS), Windows_NT)
LDFLAGS = -lws2_32 -lpthread -lglfw3 -lgdi32 -lglad
REMOVE = rmdir /s /q
else
LDFLAGS = -lpthread -lm -lglfw3 -lgdi32 -lglad
REMOVE = rm -rf
endif

$(FINAL): $(OBJ_FILES)
	$(CC) $^ $(LDFLAGS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir $@

clean_all: clean

clean:
	$(REMOVE) $(OBJ_DIR)