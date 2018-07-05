#ifndef HUD_H
#define HUD_H

#include "player.h"

// The class responsible for displaying information about the player on top of the screen.

class HUD
{
	Sprite hp_bar;			// visual representation of the player health bar
	Sprite hp_unit_digit;	// numerical representation of the player hp (last digit)
	Player *player;			// player character whose stats are shown

public:
	HUD();
	HUD(Graphics &graphics, Player &p);

	void draw(Graphics &graphics);
	void update(int elapsed_time);
};

#endif