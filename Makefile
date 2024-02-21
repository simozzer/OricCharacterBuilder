#NO_LIB=1

SRC=main.c print.s characters.s keys.s
BIN=hello_world_advanced
OBJ=$(SRC:.c=.o)
OBJ+=$(SRC:.s=.o)
include ../../rules.mk

all: $(DATA) $(SRC) $(BIN)

