PRODUCT = CaveStoryRemake.exe
SRCLIST = $(wildcard src/*.cpp)
OBJLIST = $(patsubst src/%.cpp,obj/%.o,$(SRCLIST))
FLAGS = -g -Wall -Wextra -pedantic -pedantic-errors
COMP = g++

bin/$(PRODUCT) : $(OBJLIST)
	$(COMP) -L'E:\Program Files\SDL2-2.0.4\i686-w64-mingw32\lib' $(FLAGS) $^ -lmingw32 -lSDL2main -lSDL2 -o $@

obj/%.o : src/%.cpp
	$(COMP) -I'E:\Program Files\SDL2-2.0.4\i686-w64-mingw32\include' -I'inc' $(FLAGS) -c $^ -o $@