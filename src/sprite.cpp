#include <iostream>
#include "graphics.h"
#include "sprite.h"

Sprite::Sprite()
{
	spritesheet = NULL;
}

Sprite::Sprite(Graphics &graphics, std::string file_path, int src_x, int src_y, int h, int w, float start_x, float start_y):
	pos_x(start_x), pos_y(start_y)
{
	src_rect.x = src_x;
	src_rect.y = src_y;
	src_rect.h = h;
	src_rect.w = w;
	
	spritesheet = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage(file_path));
	if(!spritesheet)
		std::cerr << "ERROR: Unable to load image." << std::endl;
}

Sprite::~Sprite() {}

void Sprite::draw(Graphics &graphics, int x, int y)
{
	SDL_Rect dest_rect = { x, y, src_rect.w, src_rect.h };
	graphics.blitSurface(spritesheet, &src_rect, &dest_rect);
}

void Sprite::update() {}