#ifndef PLAYER_H
#define PLAYER_H

#include "animated_sprite.h"
#include "level.h"

// Player constants.
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
	unsigned int current_hp, max_hp;	// how much HP the player has at the moment, and how much can he have at most
	float dx, dy;						// movement offset
	Direction facing;					// direction that the player is facing

	// Status booleans.
	bool looking_up;	// true if player is looking up
	bool looking_down;	// true if player is looking down
	bool on_ground;		// false if player is in mid air
	
public:

	Player();
	Player(Graphics &graphics, Vector2 spawn_point);
	
	inline void reduceHP() { --current_hp; }
	int getCurrentHP();
	int getMaxHP();
	
	void draw(Graphics &graphics);
	void update(float elapsed_time);
	
	virtual void animationDone(std::string name);
	void handleDoorCollision(std::vector<Door> &doors, Level &level, Graphics &graphics);
	void handleSlopeCollisions(std::vector<Slope> &slopes);
	void handleTileCollisions(std::vector<Rectangle> &rects);
	virtual void setupAnimations();
	
	void jump();
	void moveLeft();
	void moveRight();
	void stopMoving();

	void lookUp();
	void stopLookingUp();
	void lookDown();
	void stopLookingDown();
};

#endif