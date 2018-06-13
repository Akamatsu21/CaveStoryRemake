#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "globals.h"

// Class representing a rectangle that bounds a game sprite.

class Rectangle
{
	int pos_x, pos_y, width, height; // location and size of the rectangle

public:

	// Default constructor.
	Rectangle():
		pos_x(0), pos_y(0), width(0), height(0)
	{}
	
	// Constructor.
	Rectangle(int x, int y, int w, int h):
		pos_x(x), pos_y(y), width(w), height(h)
	{}
	
	// Get coordinates of the rectangle's centre.
	int centerX() {	return pos_x + width / 2; }
	int centerY() {	return pos_y + height / 2; }
	
	// Getters for width and height.
	int getHeight() { return height; }
	int getWidth() { return width; }
	
	// Getters for sides coordinates.
	int bottomBorder() { return pos_y + height; }
	int leftBorder() { return pos_x; }
	int rightBorder() { return pos_x + width; }
	int topBorder() { return pos_y; }
	
	// Convert the side enum into a numerical value.
	int side(sides::Side s)
	{
		switch(s)
		{
			case sides::TOP_SIDE:
				return topBorder();
			case sides::BOTTOM_SIDE:
				return bottomBorder();
			case sides::LEFT_SIDE:
				return leftBorder();
			case sides::RIGHT_SIDE:
				return rightBorder();
			default:
				return sides::NO_SIDE;
		}
	}
	
	// Check if this and r are colliding.
	bool collides(Rectangle &r)
	{
		return rightBorder() >= r.leftBorder() && leftBorder() <= r.rightBorder() && topBorder() <= r.bottomBorder() && bottomBorder() >= r.topBorder();
	}
	
	// Check if rectangle is mathematically possible.
	bool isValid()
	{
		return pos_x >= 0 && pos_y >= 0 && width >= 0 && height >= 0;
	}
};

#endif