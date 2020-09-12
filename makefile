CPP  = g++
OBJ = main.o \
	  util.o \
	  classes/display.o \
	  classes/glwindow.o
LIBS=-lSDLmain -lSDL -lGL -lGLU
FLAGS=

all: cubo

clean:
	rm -rf $(OBJ) cubo

cubo: $(OBJ)
	$(CPP) -o cubo $(OBJ) $(LIBS)

main.o: main.cpp
	$(CPP) -c main.cpp -o main.o $(FLAGS)
util.o: util.cpp
	$(CPP) -c util.cpp -o util.o $(FLAGS)

classes/glwindow.o: classes/glwindow.cpp
	$(CPP) -c classes/glwindow.cpp -o classes/glwindow.o $(FLAGS)

classes/display.o: classes/display.cpp
	$(CPP) -c classes/display.cpp -o classes/display.o $(FLAGS)
