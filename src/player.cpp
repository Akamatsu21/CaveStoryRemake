#include "graphics.h"
#include "player.h"

Player::Player():
	AnimatedSprite()
{
	dx = 0;
	dy = 0;
	facing = RIGHT;
	on_ground = false;
}

Player::Player(Graphics &graphics, float x, float y):
	AnimatedSprite(graphics, "..\\content\\sprites\\MyChar.png", 0, 0, 16, 16, x, y, 100), dx(0), dy(0), facing(RIGHT), on_ground(false)
{
	graphics.loadImage("..\\content\\sprites\\MyChar.png");
	setupAnimations();
	playAnimation("IdleRight");
}

void Player::animationDone(std::string name)
{
	
}

void Player::draw(Graphics &graphics)
{
	AnimatedSprite::draw(graphics, pos_x, pos_y);
}

float Player::getX()
{
	return pos_x;
}

float Player::getY()
{
	return pos_y;
}

void Player::moveLeft()
{
	dx = -stats::SPEED;
	facing = LEFT;
	playAnimation("RunLeft");
}

void Player::moveRight()
{
	dx = stats::SPEED;
	facing = RIGHT;
	playAnimation("RunRight");
}

void Player::setupAnimations()
{
	addAnimation(1, 0, 0, "IdleLeft", 16, 16, Vector2(0, 0));
	addAnimation(1, 0, 1, "IdleRight", 16, 16, Vector2(0, 0));
	addAnimation(3, 0, 0, "RunLeft", 16, 16, Vector2(0, 0));
	addAnimation(3, 0, 1, "RunRight", 16, 16, Vector2(0, 0));
}

void Player::stopMoving()
{
	dx = 0;
	playAnimation(facing == RIGHT ? "IdleRight" : "IdleLeft");
}
	
void Player::update(float elapsed_time)
{
	//apply gravity
	if(dy <= stats::GRAVITY_CAP)
	{
		dy += stats::GRAVITY * elapsed_time;
	}
	
	//move by dx
	pos_x += dx * elapsed_time;
	
	//move by dy
	pos_y += dy * elapsed_time;
	
	AnimatedSprite::update(elapsed_time);
}