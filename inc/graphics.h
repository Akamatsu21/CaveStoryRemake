#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <map>
#include <string>

struct SDL_Rect;
class SDL_Renderer;
class SDL_Surface;
struct SDL_Texture;
class SDL_Window;

// The class responsible for dealing with game graphics.

class Graphics
{
	std::map<std::string, SDL_Surface*> spritesheets;	// set of all spritesheets used in the game
	SDL_Renderer *renderer;								// graphics renderer
	SDL_Window *window;									// game window
	
public:
	Graphics();
	~Graphics();
	
	SDL_Renderer* getRenderer();
	
	void blitSurface(SDL_Texture *image, SDL_Rect *src, SDL_Rect *dest);
	void clear();
	void flip();
	SDL_Surface* loadImage(const std::string &file_path);
};

#endif