#include "input.h"

void Input::beginNewFrame()
{
	pressed_keys.clear();
	released_keys.clear();
}

bool Input::isHeld(SDL_Scancode key)
{
	return held_keys[key];
}

void Input::keyDownEvent(SDL_Event &event)
{
	pressed_keys[event.key.keysym.scancode] = true;
	held_keys[event.key.keysym.scancode] = true;
}

void Input::keyUpEvent(SDL_Event &event)
{
	released_keys[event.key.keysym.scancode] = true;
	held_keys[event.key.keysym.scancode] = false;
}

bool Input::wasPressed(SDL_Scancode key)
{
	return pressed_keys[key];
}

bool Input::wasReleased(SDL_Scancode key)
{
	return released_keys[key];
}