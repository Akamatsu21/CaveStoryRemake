#include "graphics.h"
#include "enemy.h"

/******* Base Enemy class *******/

// Default constructor.
Enemy::Enemy()
{
	current_hp = 0;
	max_hp = 0;
	facing = LEFT;
}

// Constructor.
Enemy::Enemy(Graphics &graphics, std::string file_path, int src_x, int src_y, int h, int w, Vector2 spawn_point, float time):
	AnimatedSprite(graphics, file_path, src_x, src_y, h, w, spawn_point.x, spawn_point.y, time), current_hp(0), max_hp(0), facing(LEFT)
{}

// Getter for current_hp.
int Enemy::getCurrentHP()
{
	return current_hp;
}

// Getter for max_hp.
int Enemy::getMaxHP()
{
	return max_hp;
}

/******* Bat *******/

// Default constructor.
Bat::Bat()
{}

// Constructor.
Bat::Bat(Graphics &graphics, Vector2 spawn_point):
	Enemy(graphics, "..\\content\\sprites\\NpcCemet.png", 32, 32, 16, 16, spawn_point, 140)
{
	setupAnimations();
	playAnimation("FlyLeft");
}

// Logic to execute after an animation finishes.
void Bat::animationDone(std::string name)
{}

// Draw bat sprite onto the screen.
void Bat::draw(Graphics &graphics)
{
	AnimatedSprite::draw(graphics, pos_x, pos_y);
}

// Set the bat animations.
void Bat::setupAnimations()
{
	addAnimation(3, 2, 2, "FlyLeft", 16, 16, Vector2(0, 0));
	addAnimation(3, 2, 3, "FlyRight", 16, 16, Vector2(0, 0));
}

// Update sprite position.
void Bat::update(int elapsed_time, Player &player)
{
	facing = (player.getX() > pos_x ? RIGHT : LEFT);
	playAnimation(facing == RIGHT ? "FlyRight" : "FlyLeft");

	AnimatedSprite::update(elapsed_time);
}