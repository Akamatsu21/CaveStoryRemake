#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include "globals.h"

class Graphics;
struct SDL_Texture;

//The class holding the information for map backgrounds

class Level
{
	SDL_Texture *background;
	std::string map_name;
	Vector2 size;
	Vector2 spawn_point;
	
	void loadMap(Graphics &graphics, std::string name); //load a map image
	
public:
	Level();
	Level(Graphics &graphics, std::string name, Vector2 point);
	~Level();
	
	void draw(Graphics &graphics);
	void update(float elapsed_time);
};

#endif