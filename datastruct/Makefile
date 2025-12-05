# CC = gcc
# CFLAGS = -Wall -g -Iinclude -Incurses
# SRC = src/list.c src/ds_common.c src/visual.c
# OBJ = $(SRC:.c=.o)
# TEST = test/test_list.c

# all: test_list

# test_list: $(OBJ) $(TEST)
# 	$(CC) $(CFLAGS) $^ -o $@

# clean:
# 	rm -f src/*.o test_list


# CC = gcc
# CFLAGS = -Wall -g -Iinclude
# SRC = src/bst.c src/ds_common.c
# OBJ = $(SRC:.c=.o)
# TEST = test/test_bst.c

# all: test_bst

# test_bst: $(OBJ) $(TEST)
# 	$(CC) $(CFLAGS) $^ -o $@

# clean:
# 	rm -f src/*.o test_bst


# CC = gcc
# CFLAGS = -Wall -g -Iinclude
# LDFLAGS = -lncurses
# SRC = src/list.c src/ds_common.c src/visual.c
# OBJ = $(SRC:.c=.o)
# TEST = test/test_list.c

# all: test_list

# test_list: $(OBJ) $(TEST)
# 	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

# clean:
# 	rm -f src/*.o test_list

# CC = gcc
# CFLAGS = -Wall -g -Iinclude
# LDFLAGS = -lncurses
# SRC = src/bst.c src/ds_common.c src/visual.c
# OBJ = $(SRC:.c=.o)
# TEST = test/test_bst.c

# all: test_bst

# test_bst: $(OBJ) $(TEST)
# 	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

# clean:
# 	rm -f src/*.o test_bst

CC = gcc
CFLAGS = -Wall -g -Iinclude
LDFLAGS = -lncurses
SRC = src/list.c src/ds_common.c src/visual.c src/bst.c
OBJ = $(SRC:.c=.o)
TEST = test/test_api.c

all: test_api

test_api: $(OBJ) $(TEST)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

clean:
	rm -f src/*.o test_api