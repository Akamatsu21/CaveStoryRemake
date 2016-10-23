#ifndef GLOBALS_H
#define GLOBALS_H

enum Direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

namespace globals
{
	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;
	const int SPRITE_SCALE = 2; 
}

struct Vector2
{
	int x, y;
	
	Vector2():
		x(0), y(0)
	{}

	Vector2(int coord_x, int coord_y):
		x(coord_x), y(coord_y)
	{}
};

#endif