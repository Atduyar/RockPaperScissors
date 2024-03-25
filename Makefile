CC=g++
CFLAGS= -std=c++17 \
	-Wall \
	-I"lib" \
	`sdl2-config --cflags` \
LIBS= `sdl2-config --libs` \
	-lSDL2main \
	-lSDL2_image \
	-lSDL2_ttf

SRC=src
OBJ=obj

SRCS=$(wildcard $(SRC)/*.cpp)
OBJS=$(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(SRCS))

BINDIR=bin
BIN=$(BINDIR)/main

$(BIN): $(OBJS) 
	mkdir -p $(BINDIR)
	$(CC) $^ -o $@ $(CFLAGS) 
	$(info ----compile $@----)

$(OBJ)/%.o: $(SRC)/%.cpp
	mkdir -p $(OBJ)
	$(CC) $(CFLAGS) -c $< -o $@
	$(info ----compile $@----)

info:
	$(info OBJS: $(OBJS)) 
	$(info SRCS: $(SRCS)) 
rm:
	rm $(OBJS)
clear:
	clear
line:
	$(info ----   start   ----)
s: clear line
	./$(BIN)

make: clear $(BIN)
run: s line
cr: clear $(BIN) line
	./$(BIN)

echo:
	$(info "OBJS: $(OBJS)")
	$(info "SRCS: $(SRCS)")
	$(info "BIN: $(BIN)")
	$(info "CFLAGS: $(CFLAGS)")
	$(info "clang_format: clang-format --dump-config --style='{BasedOnStyle: Google, IndentWidth: 4, TabWidth: 4, AccessModifierOffset: -4}' > .clang-format")
