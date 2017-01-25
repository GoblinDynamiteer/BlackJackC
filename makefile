TARGET = blackjackc
LIBS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf
CC = gcc
CFLAGS = -g -Wall
SUBDIR = game
SRC = main.c $(wildcard $(SUBDIR)/*.c)
OBJ = $(SRC:.c=.o)

all: cleantarget blackjack run

blackjack: $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LIBS)

main.o : main.c def.h
	$(CC) -c main.c

game.o : $(SUBDIR)/game.c def.h
	$(CC) -c game.c

cycles.o : $(SUBDIR)/cycles.c def.h
	$(CC) -c cycles.c

num.o : $(SUBDIR)/num.c def.h
	$(CC) -c num.c

play.o : $(SUBDIR)/play.c def.h
	$(CC) -c play.c

clean:
	-rm -f *.o
	-rm -f $(SUBDIR)/*.o
	-rm -f $(TARGET).*

cleantarget:
		-rm -f $(TARGET).*

run: $(TARGET)
	.\$(TARGET)
