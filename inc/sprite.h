#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2\SDL.h>

//The class holding information for sprites

class Sprite
{
	float pos_x, pos_y;
	SDL_Texture* spritesheet;
	SDL_Rect src_rect;
	
public:
	Sprite();
	Sprite(Graphics &graphics, std::string file_path, int src_x, int src_y, int h, int w, float start_x, float start_y);
	virtual ~Sprite();
	
	void draw(Graphics &graphics, int x, int y);
	virtual void update();
};
#endif