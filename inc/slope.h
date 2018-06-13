#ifndef SLOPE_H
#define SLOPE_H

#include <cmath>
#include "rectangle.h"

// The class responsible for drawing slopes.

class Slope
{
	Vector2 point1;	// start point
	Vector2 point2;	// end point
	float slope;	// slope angle value

public:
	// Default constructor.
	Slope():
		slope(0)
	{}
	
	// Constructor.
	Slope(Vector2 p1, Vector2 p2):
		point1(p1), point2(p2)
	{
		// The slope can't be a horizontal line.
		if(point2.x - point1.x != 0)
		{
			slope = ((std::fabs(point2.y) - std::fabs(point1.y)) / (std::fabs(point2.x) - std::fabs(point1.x)));
		}
	}
	
	// True if r is colliding with this slope.
	bool collides(Rectangle &r)
	{
		return (r.rightBorder() >= point2.x && r.leftBorder() <= point1.x && r.topBorder() <= point2.y && r.bottomBorder() >= point1.y) ||
			   (r.rightBorder() >= point1.x && r.leftBorder() <= point2.x && r.topBorder() <= point1.y && r.bottomBorder() >= point2.y) ||
			   (r.leftBorder() <= point1.x && r.rightBorder() >= point2.x && r.topBorder() <= point1.y && r.bottomBorder() >= point2.y) ||
			   (r.leftBorder() <= point2.x && r.rightBorder() >= point1.x && r.topBorder() <= point2.y && r.bottomBorder() >= point1.y);
	}
	
	// Getter for point1.
	Vector2 getPoint1()
	{
		return point1;
	}
	
	// Getter for point2.
	Vector2 getPoint2()
	{
		return point2;
	}
	
	// Getter for slope.
	float getSlope()
	{
		return slope;
	}
};

#endif