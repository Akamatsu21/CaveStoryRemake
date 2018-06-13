#ifndef SPRITE_H
#define SPRITE_H

#include <string>
#include <SDL2\SDL.h>
#include "rectangle.h"

class Graphics;

// The class holding information for sprites.

class Sprite
{

protected:
	Rectangle bounding_box;		// rectangle around the sprite, needed for collisions
	float pos_x, pos_y;			// sprite position on the screen
	SDL_Texture* spritesheet;	// spritesheet containing animation frames
	SDL_Rect src_rect;			// current image of the sprite
	
public:
	Sprite();
	Sprite(Graphics &graphics, std::string file_path, int src_x, int src_y, int h, int w, float start_x, float start_y);
	virtual ~Sprite();
	
	void draw(Graphics &graphics, int x, int y);
	virtual void update();
	
	sides::Side collisionSide(Rectangle &rect);
	Rectangle& getBoundingBox();
};

#endif