#ifndef HUD_H
#define HUD_H

#include "player.h"

// The class responsible for displaying information about the player on top of the screen.

class HUD
{
	// HP sprites.
	Sprite current_hp;		// visual representatio of the player hp
	Sprite hp_bar;			// visual representation of the player health bar
	Sprite hp_unit_digit;	// numerical representation of the player hp (last digit)

	// EXP sprites.
	Sprite exp_bar;		// visual representation of the player experience bar
	Sprite lvl_number;	// numerical representation of the player level
	Sprite lvl_label;	// the word "LVL" next to the level number

	// Weapon info sprites. For now just the visual elements.
	Sprite slash_separator;
	Sprite dash_placeholders;

	Player *player;	// player character whose stats are shown

public:
	HUD();
	HUD(Graphics &graphics, Player &p);

	void draw(Graphics &graphics);
	void update(int elapsed_time);
};

#endif