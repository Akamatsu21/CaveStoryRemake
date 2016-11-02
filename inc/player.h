#ifndef PLAYER_H
#define PLAYER_H

#include "animated_sprite.h"

//Player constants

namespace stats
{
	const float GRAVITY = 0.002f;
	const float GRAVITY_CAP = 0.8f;
	const float SPEED = 0.2f;
}

// The class holding information about the player character.

class Player: public AnimatedSprite
{
	float dx, dy;
	Direction facing;
	bool on_ground;
	
public:

	Player();
	Player(Graphics &graphics, float x, float y);
	
	inline float getX();
	inline float getY();
	
	void draw(Graphics &graphics);
	void update(float elapsed_time);
	
	virtual void animationDone(std::string name);
	virtual void setupAnimations();
	
	void moveLeft(); //move the player by -dx
	void moveRight(); //move the player by +dx
	void stopMoving(); //play the idle animation
};

#endif