TARGET = blackjackc
LIBS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf
CC = gcc
SRC_EXT = c
OBJ_EXT = o
CFLAGS = -g -Wall
SUBDIR = game
HEADER = def.h
SRC = $(wildcard *.$(SRC_EXT)) $(wildcard $(SUBDIR)/*.$(SRC_EXT))
OBJ = $(SRC:.$(SRC_EXT)=.$(OBJ_EXT))

#Remove executable -> build -> run
all: cleantarget link run

link: $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LIBS)

#Compile object files from sources if needed
$(OBJ) : $(HEADER)

#Remove object files and executable
clean:
	-rm -f *.$(OBJ_EXT)
	-rm -f $(SUBDIR)/*.$(OBJ_EXT)
	-rm -f $(TARGET).*

#Remove executable
cleantarget:
		-rm -f $(TARGET).*

#Run executable
run: $(TARGET)
	.\$(TARGET)
