#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <vector>
#include "animated_tile.h"
#include "slope.h"

class Graphics;
struct SDL_Texture;
struct Tileset;

// The class holding the information for map backgrounds.

class Level
{
	SDL_Texture *background;	// image of the map
	std::string map_name;		// name of the map
	Vector2 map_size;			// size of the map
	Vector2 spawn_point;		// coordinates where the player starts
	Vector2 tile_size;			// size of a single tile
	
	std::vector<Rectangle> collision_rects;	// all collision rectangles on the map
	std::vector<Slope> slopes;				// all slopes on the map
	std::vector<Tile> tiles;				// all tiles on the map
	std::vector<Tileset> tilesets;			// all tilesets used in the map

	std::vector<AnimatedTile> animated_tiles;		// all tiles on this level that have animations
	std::vector<AnimatedTileInfo> animations_info;	// dataset for each animation
	
	void loadMap(Graphics &graphics);
	Vector2 getTilesetPosition(Tileset *tset, int gid, int tile_width, int tile_height);
	
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

// Structure representing a tileset used for level mapping.
struct Tileset
{
	int first_gid;		// first gid of this tileset
	SDL_Texture *image;	// tileset image
	
	// Default constructor.
	Tileset()
	{
		first_gid = -1;
		image = nullptr;
	}
	
	// Constructor.
	Tileset(SDL_Texture *texture, int first)
	{
		first_gid = first;
		image = texture;
	}
};

#endif