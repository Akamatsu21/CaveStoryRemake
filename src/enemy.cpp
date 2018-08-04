#include "graphics.h"
#include "player.h"
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
	AnimatedSprite(graphics, file_path, src_x, src_y, h, w, spawn_point.x, spawn_point.y, time),
	current_hp(0), max_hp(0), facing(LEFT)
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
{
	start_x = 0;
	start_y = 0;
}

// Constructor.
Bat::Bat(Graphics &graphics, Vector2 spawn_point):
	Enemy(graphics, "..\\content\\sprites\\NpcCemet.png", 32, 32, 16, 16, spawn_point, 140),
	start_x(spawn_point.x), start_y(spawn_point.y), moving_up(false)
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

// Deal 1 damage to the player on contact.
void Bat::touchPlayer(Player *player)
{
	player->modifyHP(-1);
}

// Update sprite position.
void Bat::update(int elapsed_time, Player &player)
{
	// Decide facing based on player facing.
	facing = (player.getX() > pos_x ? RIGHT : LEFT);
	playAnimation(facing == RIGHT ? "FlyRight" : "FlyLeft");

	// Moving up or down.
	pos_y += (moving_up ? -0.02 : 0.02);
	if(pos_y > start_y + 20 || pos_y < start_y - 20)
	{
		moving_up = !moving_up; // change the value to opposite
	}

	AnimatedSprite::update(elapsed_time);
}