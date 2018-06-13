#ifndef ANIMATED_TILE_H
#define ANIMATED_TILE_H

#include <vector>
#include "tile.h"

class Graphics;
struct SDL_Texture;

// The class responsible for animated tiles.

class AnimatedTile: public Tile
{
	std::vector<Vector2> tileset_positions;	// positions of each frame on the tileset
	unsigned int current_tile;				// the tile to draw next
	int duration;							// duration of each frame
protected:
	int time_left;	// time left till the next frame
	bool finished;	// true if animation finished
public:
	AnimatedTile();
	AnimatedTile(std::vector<Vector2> positions, int dur, SDL_Texture *tileset_image, Vector2 tile_size, Vector2 map_pos);

	void draw(Graphics &graphics);
	void update(float elapsed_time);
};

// Structure holding information regarding a tile animation.
struct AnimatedTileInfo
{
	int first_gid;				// first gid of the tileset
	int first_tile_id;			// id number of the first tile in the animation
	int duration;				// duration of each frame
	std::vector<int> tile_ids;	// tile id of each frame
};

#endif