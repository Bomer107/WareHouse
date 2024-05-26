Compiler := g++

Flags := -g -Wall -Weffc++ -std=c++11 -Iinclude

Src_files := $(wildcard src/*.cpp)

Obj_files := $(patsubst src/%.cpp, bin/%.o, $(Src_files))

Executable := bin/warehouse

all: clean $(Executable)

$(Obj_files): bin/%.o: src/%.cpp
	$(Compiler) $(Flags) -c $< -o $@

$(Executable): $(Obj_files)
	$(Compiler) $(Flags) $^ -o $@

clean:
	rm -f bin/*
