#include <SDL2/SDL.h>
#include "graphics.h"
#include "level.h"

Level::Level()
{
	background = NULL;
	map_name = "";
	map_size = Vector2(0, 0);
	spawn_point = Vector2(0, 0);
	tile_size = Vector2(0, 0);
}
Level::Level(Graphics &graphics, std::string name, Vector2 point):
	map_name(name), map_size(Vector2(0, 0)), spawn_point(point), tile_size(Vector2(0,0))
{
	loadMap(graphics, map_name);
}

Level::~Level()
{
	
}

void Level::loadMap(Graphics &graphics, std::string name)
{
	//TEMPORARY
	background = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage("..\\content\\backgrounds\\bkBlue.png"));
	map_size = Vector2(1280, 960);
}


void Level::draw(Graphics &graphics)
{
	SDL_Rect src = { 0, 0, 64, 64 };
	SDL_Rect dest = { 0, 0, 64 * globals::SPRITE_SCALE, 64 * globals::SPRITE_SCALE };
	
	for(unsigned int x = 0; x < map_size.x; x += 64)
	{
		for(unsigned int y = 0; y < map_size.y; y += 64)
		{
			dest.x = x * globals::SPRITE_SCALE;
			dest.y = y * globals::SPRITE_SCALE;
			graphics.blitSurface(background, &src, &dest);
		}
	}
}

void Level::update(float elapsed_time)
{
	
}