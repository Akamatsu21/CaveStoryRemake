#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "globals.h"

class Rectangle
{
	int pos_x, pos_y, width, height;
	
public:

	Rectangle():
		pos_x(0), pos_y(0), width(0), height(0)
	{}
	
	Rectangle(int x, int y, int w, int h):
		pos_x(x), pos_y(y), width(w), height(h)
	{}
	
	int centerX() {	return pos_x + width / 2; }
	int centerY() {	return pos_y + height / 2; }
	
	int getHeight() { return height; }
	int getWidth() { return width; }
	
	int bottomBorder() { return pos_y + height; }
	int leftBorder() { return pos_x; }
	int rightBorder() { return pos_x + width; }
	int topBorder() { return pos_y; }
	
	int side(sides::Side s)
	{
		switch(s)
		{
			case TOP_SIDE:
				return topBorder();
			case BOTTOM_SIDE:
				return bottomBorder();
			case LEFT_SIDE:
				return leftBorder();
			case RIGHT_SIDE:
				return rightBorder();
			default:
				return NO_SIDE;
		}
	}
	
	//check if this and r are colliding
	bool collides(Rectangle &r)
	{
		return rightBorder() >= r.leftBorder() && leftBorder() <= r.rightBorder() && topBorder() <= r.bottomBorder() && bottomBorder() >= r.topBorder();
	}
	
	bool isValid()
	{
		return pos_x >= 0 && pos_y >= 0 && width >= 0 && height >= 0;
	}
};

#endif