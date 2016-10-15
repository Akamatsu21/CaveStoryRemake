#ifndef INPUT_H
#define INPUT_H

#include <map>
#include <SDL2\SDL.h>

//The class responsible for managing input from the keyboard.

class Input
{
	std::map<SDL_Scancode, bool> held_keys;
	std::map<SDL_Scancode, bool> pressed_keys;
	std::map<SDL_Scancode, bool> released_keys;
	
public:
	void beginNewFrame();	//reset all keys at the beginning of every frame
	bool isHeld(SDL_Scancode key);	//is key held right now
	void keyDownEvent(SDL_Event &event);	//called on key press
	void keyUpEvent(SDL_Event &event);	//called on key release
	bool wasPressed(SDL_Scancode key);	//was key pressed this frame
	bool wasReleased(SDL_Scancode key);	//was key released this frame
};

#endif