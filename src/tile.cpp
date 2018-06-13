#include <SDL2\SDL.h>
#include "graphics.h"
#include "tile.h"

// Default constructor.
Tile::Tile()
{
	map_pos = size = tileset_pos = Vector2(0, 0);
	tileset = nullptr;
}

// Constructor.
Tile::Tile(SDL_Texture *tileset_image, Vector2 tile_size, Vector2 ts_pos, Vector2 mp_pos):
	map_pos(Vector2(mp_pos.x * globals::SPRITE_SCALE, mp_pos.y * globals::SPRITE_SCALE)), size(tile_size), tileset(tileset_image), tileset_pos(ts_pos)
{}

// Draw tile on the screen.
void Tile::draw(Graphics &graphics)
{
	SDL_Rect src = { tileset_pos.x, tileset_pos.y, size.x, size.y };
	SDL_Rect dest = { map_pos.x, map_pos.y, size.x * globals::SPRITE_SCALE, size.y * globals::SPRITE_SCALE };
	graphics.blitSurface(tileset, &src, &dest);
}

// Update tile on the screen.
void Tile::update(float elapsed_time)
{}