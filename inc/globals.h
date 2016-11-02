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

namespace sides
{
	enum Side
	{
		NO_SIDE,
		TOP_SIDE,
		BOTTOM_SIDE,
		LEFT_SIDE,
		RIGHT_SIDE
	};
	
	inline Side oppositeSide(Side s)
	{
		switch(s)
		{
			case TOP_SIDE:
				return BOTTOM_SIDE;
			case BOTTOM_SIDE:
				return TOP_SIDE;
			case LEFT_SIDE:
				return RIGHT_SIDE;
			case RIGHT_SIDE:
				return LEFT_SIDE;
			default:
				return NO_SIDE;
		}
	}
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