CC := gcc
INCLUDE := -I./include
CFLAGS := -O2 -Wall -Wextra
DEBUG := -O0 -g3 -Wall -Wextra -fsanitize=address,undefined -fno-omit-frame-pointer

SRCS := $(shell find ./ -name "*.c")
OUT := build/EC.out

.PHONY: all clean again

all: clean build

build: $(OUT)

$(OUT):
	$(CC) $(CFLAGS) $(INCLUDE) $(SRCS) -o $(OUT) 

debug: clean
	$(CC) $(DEBUG) $(INCLUDE) $(SRCS) -o $(OUT) 

clean:
	rm -f $(OUT)