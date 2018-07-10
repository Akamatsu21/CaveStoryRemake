#include <iostream>
#include <SDL2\SDL.h>
#include <SDL2\SDL_image.h>
#include "globals.h"
#include "graphics.h"

// Default constructor.
Graphics::Graphics()
{
	window = nullptr;
	renderer = nullptr;
}

// Draws image to the screen.
void Graphics::blitSurface(SDL_Texture *image, SDL_Rect *src, SDL_Rect *dest)
{
	SDL_RenderCopy(renderer, image, src, dest);
}

// Clear the renderer.
void Graphics::clear()
{
	SDL_RenderClear(renderer);
}

// Render the screen onto the window.
void Graphics::flip()
{
	SDL_RenderPresent(renderer);
}

// Initialise window.
void Graphics::init()
{
	SDL_CreateWindowAndRenderer(globals::SCREEN_WIDTH, globals::SCREEN_HEIGHT, 0, &window, &renderer);
	SDL_SetWindowTitle(window, "Cavestory");
}

// Getter for the renderer.
SDL_Renderer* Graphics::getRenderer()
{
	return renderer;
}

// Load image into spritesheets if it doesn't already exist, either way returns the the image.
SDL_Surface* Graphics::loadImage(const std::string &file_path)
{
	if(spritesheets.count(file_path) == 0)
	{
		spritesheets[file_path] = IMG_Load(file_path.c_str());
	}
	
	if(spritesheets[file_path] == nullptr) 
	{
        std::cerr << "ERROR: image load failed: " << SDL_GetError() << std::endl;
        return nullptr;
    }
	
	return spritesheets[file_path];
}

Graphics::~Graphics()
{
	std::cout << "Window destroyed";
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
}