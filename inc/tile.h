#ifndef TILE_H
#define TILE_H

#include "globals.h"

class Graphics;
struct SDL_Texture;

// The class responsible for drawing tiles.

class Tile
{
protected:
	Vector2 map_pos;		// tile position on the screen
	Vector2 size;			// tile height and width
	SDL_Texture *tileset;	// tileset image
	Vector2 tileset_pos;	// tile position on the tileset
	
public:

	Tile();
	Tile(SDL_Texture *tileset_image, Vector2 tile_size, Vector2 ts_pos, Vector2 mp_pos);
	
	void draw(Graphics &graphics);
	void update(float elapsed_time);
};

#endif