#ifndef SLOPE_H
#define SLOPE_H

#include <algorithm>
#include "rectangle.h"

class Slope
{
	Vector2 point1;
	Vector2 point2;
	float slope;

public:
	Slope():
		slope(0) {}
	
	Slope(Vector2 p1, Vector2 p2):
		point1(p1), point2(p2)
	{
		if(point1.x - point2.x != 0)
		{
			slope = (fabs(point2.y - point1.y) / (fabs(point2.x - point1.x)));
		}
	}
	
	bool collides(Rectangle &r)
	{
		return (r.rightBorder() >= point2.x && r.leftBorder() <= point1.x && r.topBorder() <= point2.y && r.bottomBorder() >= point1.y) ||
			   (r.rightBorder() >= point1.x && r.leftBorder() <= point2.x && r.topBorder() <= point1.y && r.bottomBorder() >= point2.y) ||
			   (r.leftBorder() <= point1.x && r.rightBorder() >= point2.x && r.topBorder() <= point1.y && r.bottomBorder() >= point2.y) ||
			   (r.leftBorder() <= point2.x && r.rightBorder() >= point1.x && r.topBorder() <= point2.y && r.bottomBorder() >= point1.y);
	}
	
	Vector2 getPoint1()
	{
		return point1;
	}
	
	Vector2 getPoint2()
	{
		return point2;
	}
	
	float getSlope()
	{
		return slope;
	}
};

#endif