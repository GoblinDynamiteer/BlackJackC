TARGET = blackjackc
LIBS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf
CC = gcc
CFLAGS = -g -Wall
SUBDIR = game
SRC = $(wildcard *.c) $(wildcard $(SUBDIR)/*.c)

ballz:
	$(CC) $(SRC) -o $(TARGET) $(LIBS)

clean:
	-rm -f *.o
	-rm -f $(TARGET).*
	
run:
	.\$(TARGET)