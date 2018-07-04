#include "graphics.h"
#include "player.h"
#include <iostream>

// Default constructor.
Player::Player():
	AnimatedSprite()
{
	dx = 0;
	dy = 0;
	facing = RIGHT;
	on_ground = false;
	looking_up = false;
	looking_down = false;
}

// Constructor.
Player::Player(Graphics &graphics, Vector2 spawn_point):
	AnimatedSprite(graphics, "..\\content\\sprites\\MyChar.png", 0, 0, 16, 16, spawn_point.x, spawn_point.y, 100), dx(0), dy(0),
	facing(RIGHT), on_ground(false), looking_up(false), looking_down(false)
{
	graphics.loadImage("..\\content\\sprites\\MyChar.png");
	setupAnimations();
	playAnimation("IdleRight");
}

// Logic to execute after an animation finishes.
void Player::animationDone(std::string name)
{}

// Draw player sprite onto the screen.
void Player::draw(Graphics &graphics)
{
	AnimatedSprite::draw(graphics, pos_x, pos_y);
}

// Getter for pos_x.
float Player::getX()
{
	return pos_x;
}

// Getter for pos_y;
float Player::getY()
{
	return pos_y;
}

// Handles collisions with all colliding slopes.
void Player::handleSlopeCollisions(std::vector<Slope> &slopes)
{
	for(unsigned int i = 0; i < slopes.size(); ++i)
	{
		// Where on the slope the player is touching.
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

// Handles collisions with all colliding tiles.
void Player::handleTileCollisions(std::vector<Rectangle> &rects)
{
	// Check collision's side.
	for(unsigned int i = 0; i < rects.size(); ++i)
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

// Start moving up.
void Player::jump()
{
	if(on_ground)
	{
		dy = stats::JUMP_SPEED * (-1);
		on_ground = false;
	}
}

// Make the character look down.
void Player::lookDown()
{
	looking_down = true;
}

// Make the character look up.
void Player::lookUp()
{
	looking_up = true;
}


// Start moving left.
void Player::moveLeft()
{
	if(looking_down && on_ground)
	{
		// Player is in interaction mode, so not allowed to move!
		return;
	}

	dx = -stats::SPEED;
	facing = LEFT;

	// Choose correct moving animation.
	if(looking_up)
	{
		playAnimation("RunLeftLookUp");
	}
	else
	{
		playAnimation("RunLeft");
	}
}

// Start moving right.
void Player::moveRight()
{
	if(looking_down && on_ground)
	{
		// Player is in interaction mode, so not allowed to move!
		return;
	}

	dx = stats::SPEED;
	facing = RIGHT;

	// Choose correct moving animation.
	if(looking_up)
	{
		playAnimation("RunRightLookUp");
	}
	else
	{
		playAnimation("RunRight");
	}
}

// Seet the player animations.
void Player::setupAnimations()
{
	addAnimation(1, 0, 0, "IdleLeft", 16, 16, Vector2(0, 0));
	addAnimation(1, 3, 0, "IdleLeftLookUp", 16, 16, Vector2(0, 0));

	addAnimation(1, 0, 1, "IdleRight", 16, 16, Vector2(0, 0));
	addAnimation(1, 3, 1, "IdleRightLookUp", 16, 16, Vector2(0, 0));
	
	addAnimation(3, 0, 0, "RunLeft", 16, 16, Vector2(0, 0));
	addAnimation(3, 3, 0, "RunLeftLookUp", 16, 16, Vector2(0, 0));

	addAnimation(3, 0, 1, "RunRight", 16, 16, Vector2(0, 0));
	addAnimation(3, 3, 1, "RunRightLookUp", 16, 16, Vector2(0, 0));

	addAnimation(1, 6, 0, "JumpLeftLookDown", 16, 16, Vector2(0, 0));
	addAnimation(1, 6, 1, "JumpRightLookDown", 16, 16, Vector2(0, 0));

	addAnimation(1, 7, 0, "InteractLeft", 16, 16, Vector2(0, 0));
	addAnimation(1, 7, 1, "InteractRight", 16, 16, Vector2(0, 0));
}

// Stop the player looking down.
void Player::stopLookingDown()
{
	looking_down = false;
}

// Stop the player looking up.
void Player::stopLookingUp()
{
	looking_up = false;
}

// Stop horizontal movement.
void Player::stopMoving()
{
	dx = 0;

	// Choose correct standing animation.
	if(looking_up)
	{
		playAnimation(facing == RIGHT ? "IdleRightLookUp" : "IdleLeftLookUp");
	}
	else if(looking_down && on_ground)
	{
		playAnimation(facing == RIGHT ? "InteractRight" : "InteractLeft");
	}
	else if(looking_down && !on_ground)
	{
		playAnimation(facing == RIGHT ? "JumpRightLookDown" : "JumpLeftLookDown");
	}
	else
	{
		playAnimation(facing == RIGHT ? "IdleRight" : "IdleLeft");
	}
}

// Update sprite position.
void Player::update(float elapsed_time)
{
	// Apply gravity.
	if(dy <= stats::GRAVITY_CAP)
	{
		dy += stats::GRAVITY * elapsed_time;
	}
	
	// Move by dx.
	pos_x += dx * elapsed_time;
	
	// Move by dy.
	pos_y += dy * elapsed_time;
	
	AnimatedSprite::update(elapsed_time);
}