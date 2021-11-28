CC=g++
CFLAGS= -std=c++17 \
	-Wall \
	-I"C:\libsdl\include" \
	-I"lib" \
	-L"C:\libsdl\lib" \
	-lmingw32 \
	-lSDL2main \
	-lSDL2 \
	-lSDL2_image \
	-lSDL2_ttf 
SRC=src
OBJ=obj

SRCS=$(wildcard $(SRC)/*.cpp)
OBJS=$(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(SRCS))

BINDIR=bin
BIN=$(BINDIR)/main.exe
#DEPS=lib/Engine.h

$(BIN): $(OBJS) 
	$(CC) $^ -o $@ $(CFLAGS) 
	$(info ----compile $@----)

$(OBJ)/%.o: $(SRC)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@
	$(info ----compile $@----)

info:
	$(info OBJS: $(OBJS)) 
	$(info SRCS: $(SRCS)) 
rm:
	del $(patsubst $(OBJ)/%.o, $(OBJ)\\%.o, $(OBJS))
clear:
	cls
line:
	$(info ----   start   ----)
s: clear line
	./$(BIN)

make: clear $(BIN)
run: s line
cr: clear $(BIN) line
	./$(BIN)
