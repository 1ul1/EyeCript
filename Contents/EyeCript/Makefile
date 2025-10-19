CC := gcc
CFLAGS := -O2 -Wall -Wextra -I./include

SRCS := $(shell find ./ -name "*.c")
OUT := build/EC.out

.PHONY: all clean again

all: clean build

build: $(OUT)

$(OUT):
	$(CC) $(CFLAGS) $(SRCS) -o $(OUT) 

clean:
	rm -f $(OUT)