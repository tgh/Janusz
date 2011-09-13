CPP=g++
SRC=janusz.cpp
BIN=janusz
FLAGS=-lglut -lGL -lGLU

	
all: janusz 

janusz:
	@echo "Compiling files for janusz..."
	@$(CPP) $(FLAGS) -o $(BIN) $(SRC)

clean:
	@if test -e $(BIN);\
	then echo "Removing $(BIN)...";\
	rm ./$(BIN);\
	fi
