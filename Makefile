CC = gcc
CFLAGS = -Wall -Wextra -Iinclude -g
SRC = src/main.c src/cuentas.c src/archivos.c
OBJ = $(SRC:.c=.o)
OUT = minibanco


all: $(OUT)


$(OUT): $(OBJ)
$(CC) $(CFLAGS) -o $(OUT) $(OBJ)


%.o: %.c
$(CC) $(CFLAGS) -c $< -o $@


clean:
rm -f $(OBJ) $(OUT)