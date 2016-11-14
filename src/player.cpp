#include "graphics.h"
#include "player.h"
#include <iostream>

Player::Player():
	AnimatedSprite()
{
	dx = 0;
	dy = 0;
	facing = RIGHT;
	on_ground = false;
}

Player::Player(Graphics &graphics, Vector2 spawn_point):
	AnimatedSprite(graphics, "..\\content\\sprites\\MyChar.png", 0, 0, 16, 16, spawn_point.x, spawn_point.y, 100), dx(0), dy(0), facing(RIGHT), on_ground(false)
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

void Player::handleSlopeCollisions(std::vector<Slope> &slopes)
{
	for(unsigned int i = 0; i < slopes.size(); i++)
	{
		//where on the slope the player is touching
		int b = slopes[i].getPoint1().y - slopes[i].getSlope() * slopes[i].getPoint1().x;
		int center_x = bounding_box.centerX();
		int y = slopes[i].getSlope() * center_x + b;

		if(on_ground)
		{
			pos_y = y - bounding_box.getHeight();
		}
	}
	//std::cerr << pos_y << std::endl;
}

void Player::handleTileCollisions(std::vector<Rectangle> &rects)
{
	//check collision's side
	for(unsigned int i = 0; i < rects.size(); i++)
	{
		sides::Side collision_side = collisionSide(rects[i]);
		if(collision_side != sides::NO_SIDE)
		{
			switch(collision_side)
			{
				case sides::TOP_SIDE:
					dy = 0;
					pos_y = rects[i].bottomBorder() + 1;
					if(on_ground)
					{
						dx = 0;
						pos_x -= facing == RIGHT ? 0.5 : -0.5;
					}
					break;
				case sides::BOTTOM_SIDE:
					pos_y = rects[i].topBorder() - bounding_box.getHeight() - 1;
					dy = 0;
					on_ground = true;
					break;
				case sides::LEFT_SIDE:
					pos_x = rects[i].rightBorder() + 1;
					break;
				case sides::RIGHT_SIDE:
					pos_x = rects[i].leftBorder() - bounding_box.getWidth() - 1;
					break;
				default:
					break;
			}
		}
	}
}

void Player::jump()
{
	if(on_ground)
	{
		dy = stats::JUMP_SPEED * (-1);
		on_ground = false;
	}
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