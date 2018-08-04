#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <vector>
#include <memory>
#include "animated_tile.h"
#include "slope.h"
#include "door.h"

class Graphics;
class Enemy;
class Player;
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

	std::vector<Door> doors;		// all doors to other levels located on this level
	std::vector<std::shared_ptr<Enemy>> enemies;	// all enemies that spawn on this level
	
	void loadMap(Graphics &graphics);
	Vector2 getTilesetPosition(Tileset *tset, int gid, int tile_width, int tile_height);
	
public:
	Level();
	Level(Graphics &graphics, std::string name);
	~Level();
	
	void draw(Graphics &graphics);
	void update(float elapsed_time, Player &player);
	
	Vector2 getPlayerSpawnPoint();
	
	std::vector<Door> checkDoorCollisions(Rectangle &rect);
	std::vector<std::shared_ptr<Enemy>> checkEnemyCollisions(Rectangle &rect);
	std::vector<Slope> checkSlopeCollisions(Rectangle &rect);
	std::vector<Rectangle> checkTileCollisions(Rectangle &rect);
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