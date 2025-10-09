# CC = gcc
# CFLAGS = -Wall -g -Iinclude
# SRC = src/list.c src/ds_common.c
# OBJ = $(SRC:.c=.o)
# TEST = test/test_list.c

# all: test_list

# test_list: $(OBJ) $(TEST)
# 	$(CC) $(CFLAGS) $^ -o $@

# clean:
# 	rm -f src/*.o test_list
CC = gcc
CFLAGS = -Wall -g -Iinclude
SRC = src/bst.c src/ds_common.c
OBJ = $(SRC:.c=.o)
TEST = test/test_bst.c

all: test_bst

test_bst: $(OBJ) $(TEST)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f src/*.o test_bst