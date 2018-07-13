#ifndef ENEMY_H
#define ENEMY_H

#include "animated_sprite.h"
#include "player.h"

// Abstract class holding the basic information shared by all enemies.

class Enemy: public AnimatedSprite
{
protected:
	
	unsigned int current_hp, max_hp;	// how much HP the enemy has at the moment, and how much can it have at most
	Direction facing;					// direction that the enemy is facing

public:

	Enemy();
	Enemy(Graphics &graphics, std::string file_path, int src_x, int src_y, int h, int w, Vector2 spawn_point, float time);

	virtual void draw(Graphics &graphics) = 0;
	virtual void update(int elapsed_time, Player &player) = 0;

	int getCurrentHP();
	int getMaxHP();
};

/******* ENEMIES *******/

class Bat: public Enemy
{
public:

	Bat();
	Bat(Graphics &graphics, Vector2 spawn_point);

	void animationDone(std::string name);
	void draw(Graphics &graphics);
	void setupAnimations();
	void update(int elapsed_time, Player &player);
};

#endif