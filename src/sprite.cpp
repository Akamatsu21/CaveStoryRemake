#include <iostream>
#include "globals.h"
#include "graphics.h"
#include "sprite.h"

// Default constructor.
Sprite::Sprite()
{
	pos_x = 0;
	pos_y = 0;
	src_rect = { 0, 0, 0, 1 };
	spritesheet = nullptr;
}

// Constructor.
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
	
	bounding_box = Rectangle(pos_x, pos_y, src_rect.w * globals::SPRITE_SCALE, src_rect.h * globals::SPRITE_SCALE);
}

// Destructor.
Sprite::~Sprite() {}

// Determine on which side the collision is happening.
sides::Side Sprite::collisionSide(Rectangle &rect)
{
	int dr, dl, dt, db; // delta right, left, top, bottom
	dr = abs(bounding_box.rightBorder() - rect.leftBorder());
	dl = abs(rect.rightBorder() - bounding_box.leftBorder());
	dt = abs(rect.bottomBorder() - bounding_box.topBorder());
	db = abs(bounding_box.bottomBorder() - rect.topBorder());
	
	int a[4] = { dr, dl, dt, db };
	int mini = a[0];
	for(int i = 1; i < 4; ++i)
	{
		if(mini > a[i])
		{
			mini = a[i];
		}
	}
	
	
	if(mini == db)
		return sides::BOTTOM_SIDE;
	else if(mini == dt)
		return sides::TOP_SIDE;
	else if(mini == dr)
		return sides::RIGHT_SIDE;
	else if(mini == dl)
		return sides::LEFT_SIDE;
	else
		return sides::NO_SIDE;
}

// Draw sprite onto the screen.
void Sprite::draw(Graphics &graphics, int x, int y)
{
	SDL_Rect dest_rect = { x, y, src_rect.w * globals::SPRITE_SCALE, src_rect.h * globals::SPRITE_SCALE };
	graphics.blitSurface(spritesheet, &src_rect, &dest_rect);
}

// Getter for bounding box.
Rectangle& Sprite::getBoundingBox()
{
	return bounding_box;
}

// Update the bounding box position.
void Sprite::update()
{
	bounding_box = Rectangle(pos_x, pos_y, src_rect.w * globals::SPRITE_SCALE, src_rect.h * globals::SPRITE_SCALE);
}