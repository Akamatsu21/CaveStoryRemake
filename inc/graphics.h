#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <map>
#include <string>

class SDL_Rect;
class SDL_Renderer;
class SDL_Surface;
class SDL_Texture;
class SDL_Window;

//The class responsible for dealing with the game graphics.

class Graphics
{
	std::map<std::string, SDL_Surface*> spritesheets;
	SDL_Renderer *renderer;
	SDL_Window *window;
	
public:
	Graphics();
	~Graphics();
	
	SDL_Renderer* getRenderer();
	
	void blitSurface(SDL_Texture *image, SDL_Rect *src, SDL_Rect *dest); //draw image to the screen
	void clear(); //clear the renderer
	void flip(); //render the screen onto the window
	SDL_Surface* loadImage(const std::string &file_path); //load image into spritesheets if it doesn't already exist, either way returns the the image
};

#endif