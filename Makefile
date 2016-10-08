PRODUCT = CaveStoryRemake.exe
SRCLIST = $(wildcard src/*.cpp)
OBJLIST = $(patsubst src/%.cpp,obj/%.o,$(SRCLIST))
ARGS = -g -Wall -Wextra
COMP = g++

bin/$(PRODUCT) : $(OBJLIST)
	$(COMP) $(ARGS) $^ -o $@

obj/%.o : src/%.cpp
	$(COMP) $(ARGS) -c $^ -I'E:\Program Files\SDL2-2.0.4\i686-w64-mingw32\include' -L'E:\Program Files\SDL2-2.0.4\i686-w64-mingw32\lib' -o $@