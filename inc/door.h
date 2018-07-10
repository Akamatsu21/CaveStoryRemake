#ifndef DOOR_H
#define DOOR_H

#include <string>
#include "rectangle.h"

// Class representing a door to a different level.

class Door: public Rectangle
{
	std::string destination;

public:

	// Default constructor.
	Door():
		Rectangle(), destination("")
	{}

	// Constructor.
	Door(Rectangle r, std::string d):
		Rectangle(r.leftBorder() * globals::SPRITE_SCALE, r.topBorder() * globals::SPRITE_SCALE, 
				  r.getWidth() * globals::SPRITE_SCALE, r.getHeight() * globals::SPRITE_SCALE),
		destination(d)
	{}

	// Getter for destination.
	std::string getDestination()
	{
		return destination;
	}
};

#endif