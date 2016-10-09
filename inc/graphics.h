#ifndef GRAPHICS_H
#define GRAPHICS_H

//The class responsible for dealing with the game graphics.

class SDL_Window;
class SDL_Renderer;

class Graphics
{
	SDL_Window* window;
	SDL_Renderer* renderer;
	
public:
	Graphics();
	~Graphics();
};

#endif