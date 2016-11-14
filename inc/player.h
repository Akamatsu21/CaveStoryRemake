#ifndef PLAYER_H
#define PLAYER_H

#include "animated_sprite.h"
#include "slope.h"

//Player constants

namespace stats
{
	const float GRAVITY = 0.002;
	const float GRAVITY_CAP = 0.8;
	const float JUMP_SPEED = 0.7;
	const float SPEED = 0.2;
}

// The class holding information about the player character.

class Player: public AnimatedSprite
{
	float dx, dy;
	Direction facing;
	bool on_ground;
	
public:

	Player();
	Player(Graphics &graphics, Vector2 spawn_point);
	
	inline float getX();
	inline float getY();
	
	void draw(Graphics &graphics);
	void update(float elapsed_time);
	
	virtual void animationDone(std::string name);
	void handleSlopeCollisions(std::vector<Slope> &slopes);	  //handles collisions with all colliding slopes
	void handleTileCollisions(std::vector<Rectangle> &rects); //handles collisions with all colliding tiles
	virtual void setupAnimations();
	
	void jump();	   //starts jumping
	void moveLeft();   //move the player by -dx
	void moveRight();  //move the player by +dx
	void stopMoving(); //play the idle animation
};

#endif