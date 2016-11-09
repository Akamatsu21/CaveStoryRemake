#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <vector>
#include "tile.h"
#include "slope.h"

class Graphics;
struct SDL_Texture;
struct Tileset;

//The class holding the information for map backgrounds

class Level
{
	SDL_Texture *background;
	std::string map_name;
	Vector2 map_size;
	Vector2 spawn_point;
	Vector2 tile_size;
	
	std::vector<Rectangle> collision_rects;
	std::vector<Slope> slopes;
	std::vector<Tile> tiles;
	std::vector<Tileset> tilesets;
	
	void loadMap(Graphics &graphics, std::string name); //load a map image
	
public:
	Level();
	Level(Graphics &graphics, std::string name);
	~Level();
	
	void draw(Graphics &graphics);
	void update(float elapsed_time);
	
	Vector2 getPlayerSpawnPoint();
	
	std::vector<Rectangle> checkTileCollisions(Rectangle &rect);
	std::vector<Slope> checkSlopeCollisions(Rectangle &rect);
};

struct Tileset
{
	int first_gid;
	SDL_Texture *image;
	
	Tileset()
	{
		first_gid = -1;
		image = NULL;
	}
	
	Tileset(SDL_Texture *texture, int first)
	{
		first_gid = first;
		image = texture;
	}
};

#endif