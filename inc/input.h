#ifndef INPUT_H
#define INPUT_H

#include <map>
#include <SDL2\SDL.h>

//The class responsible for managing input from the keyboard.

class Input
{
	std::map<SDL_Scancode, bool> held_keys;		// keys that are being held
	std::map<SDL_Scancode, bool> pressed_keys;	// keys that were pressed this frame
	std::map<SDL_Scancode, bool> released_keys;	// keys that were released this frame
	
public:
	void beginNewFrame();
	bool isHeld(SDL_Scancode key);
	void keyDownEvent(SDL_Event &event);
	void keyUpEvent(SDL_Event &event);
	bool wasPressed(SDL_Scancode key);
	bool wasReleased(SDL_Scancode key);
};

#endif