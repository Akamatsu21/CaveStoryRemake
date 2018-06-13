#include <SDL2\SDL.h>
#include <iostream>
#include "graphics.h"
#include "animated_tile.h"

// Default constructor.
AnimatedTile::AnimatedTile():
	Tile()
{
	duration = 0;
	current_tile = 0;
	time_left = 0;
}

// Constructor.
AnimatedTile::AnimatedTile(std::vector<Vector2> positions, int dur, SDL_Texture *tileset_image, Vector2 tile_size, Vector2 map_pos):
	Tile(tileset_image, tile_size, positions.at(0), map_pos), tileset_positions(positions), current_tile(0), duration(dur), time_left(dur)
{}

// Draw tile onto the screen.
void AnimatedTile::draw(Graphics &graphics)
{
	SDL_Rect src = { tileset_positions.at(current_tile).x, tileset_positions.at(current_tile).y, size.x, size.y };
	SDL_Rect dest = { map_pos.x, map_pos.y, size.x * globals::SPRITE_SCALE, size.y * globals::SPRITE_SCALE };
	graphics.blitSurface(tileset, &src, &dest);
}

// Update to the next frame of the animation.
void AnimatedTile::update(float elapsed_time)
{
	// If the duration time is up, move to the next frame.
	if(time_left <= 0)
	{
		if(current_tile == tileset_positions.size() - 1)
			current_tile = 0;
		else
			++current_tile;

		time_left = duration;
	}
	else
	{
		time_left -= elapsed_time;
	}

	Tile::update(elapsed_time);
}