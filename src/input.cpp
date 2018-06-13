#include "input.h"

// Reset all keys at the beginning of every frame.
void Input::beginNewFrame()
{
	pressed_keys.clear();
	released_keys.clear();
}

// Is key held right now.
bool Input::isHeld(SDL_Scancode key)
{
	return held_keys[key];
}

// Called on key press.
void Input::keyDownEvent(SDL_Event &event)
{
	pressed_keys[event.key.keysym.scancode] = true;
	held_keys[event.key.keysym.scancode] = true;
}

// Called on key release.
void Input::keyUpEvent(SDL_Event &event)
{
	released_keys[event.key.keysym.scancode] = true;
	held_keys[event.key.keysym.scancode] = false;
}

// Was key pressed this frame.
bool Input::wasPressed(SDL_Scancode key)
{
	return pressed_keys[key];
}

// Was key released this frame.
bool Input::wasReleased(SDL_Scancode key)
{
	return released_keys[key];
}