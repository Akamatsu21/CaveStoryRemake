PRODUCT = CaveStoryRemake.exe
SRCLIST = $(wildcard src/*.cpp)
OBJLIST = $(patsubst src/%.cpp,obj/%.o,$(SRCLIST))
FLAGS = -g -Wall -Wextra -pedantic -pedantic-errors -std=c++11
COMP = x86_64-w64-mingw32-g++

bin/$(PRODUCT) : $(OBJLIST)
	$(COMP) -L'E:\Program Files\SDL2-2.0.4\x86_64-w64-mingw32\lib' -L'E:\Program Files\SDL2_image-2.0.1\x86_64-w64-mingw32\lib' $(FLAGS) $^ -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -o $@

obj/%.o : src/%.cpp
	$(COMP) -I'E:\Program Files\SDL2-2.0.4\x86_64-w64-mingw32\include' -I'E:\Program Files\SDL2_image-2.0.1\x86_64-w64-mingw32\include' -I'inc' $(FLAGS) -c $^ -o $@

clean:
	rm bin\*.exe
	rm obj\*.o