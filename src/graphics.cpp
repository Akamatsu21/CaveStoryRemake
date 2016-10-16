#include <iostream>
#include <SDL2\SDL.h>
#include <SDL2\SDL_image.h>
#include "globals.h"
#include "graphics.h"

Graphics::Graphics()
{
	SDL_CreateWindowAndRenderer(globals::SCREEN_WIDTH, globals::SCREEN_HEIGHT, 0, &window, &renderer);
	SDL_SetWindowTitle(window, "Cavestory");
}

void Graphics::blitSurface(SDL_Texture *image, SDL_Rect *src, SDL_Rect *dest)
{
	SDL_RenderCopy(renderer, image, src, dest);
}

void Graphics::clear()
{
	SDL_RenderClear(renderer);
}

void Graphics::flip()
{
	SDL_RenderPresent(renderer);
}
SDL_Renderer* Graphics::getRenderer()
{
	return renderer;
}

SDL_Surface* Graphics::loadImage(const std::string &file_path)
{
	if(spritesheets.count(file_path) == 0)
	{
		spritesheets[file_path] = IMG_Load(file_path.c_str());
	}
	
	if(spritesheets[file_path] == NULL) 
	{
        std::cerr << "ERROR: image load failed: " << SDL_GetError() << std::endl;
        return NULL;
    }
	
	return spritesheets[file_path];
}

Graphics::~Graphics()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
}