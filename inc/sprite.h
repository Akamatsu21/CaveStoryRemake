#ifndef SPRITE_H
#define SPRITE_H

#include <string>
#include <SDL2\SDL.h>
#include "rectangle.h"

class Graphics;

//The class holding information for sprites

class Sprite
{

protected:
	Rectangle bounding_box;
	float pos_x, pos_y;
	SDL_Texture* spritesheet;
	SDL_Rect src_rect;
	
public:
	Sprite();
	Sprite(Graphics &graphics, std::string file_path, int src_x, int src_y, int h, int w, float start_x, float start_y);
	virtual ~Sprite();
	
	void draw(Graphics &graphics, int x, int y);
	virtual void update();
	
	sides::Side collisionSide(Rectangle &rect); //determine on which side the collision is happening
	Rectangle& getBoundingBox();
};
#endif