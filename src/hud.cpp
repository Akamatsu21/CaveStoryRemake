#include <cmath>
#include "hud.h"

// Default constructor.
HUD::HUD()
{
	player = nullptr;
}

// Constructor.
HUD::HUD(Graphics &graphics, Player &p)
{
	player = &p;

	current_hp = Sprite(graphics, "..\\content\\sprites\\TextBox.png", 0, 25, 5, 39, 83, 72);
	hp_bar = Sprite(graphics, "..\\content\\sprites\\TextBox.png", 0, 40, 8, 64, 35, 70);
	hp_unit_digit = Sprite(graphics, "..\\content\\sprites\\TextBox.png", 0, 56, 8, 8, 66, 70);

	exp_bar = Sprite(graphics, "..\\content\\sprites\\TextBox.png", 0, 72, 8, 40, 83, 52);
	lvl_number = Sprite(graphics, "..\\content\\sprites\\TextBox.png", 0, 56, 8, 8, 66, 52);
	lvl_label = Sprite(graphics, "..\\content\\sprites\\TextBox.png", 81, 81, 7, 11, 38, 55);

	slash_separator = Sprite(graphics, "..\\content\\sprites\\TextBox.png", 72, 48, 8, 8, 100, 36);
	dash_placeholders = Sprite(graphics, "..\\content\\sprites\\TextBox.png", 81, 51, 11, 15, 132, 26);
}

// Draw all HUD elements.
void HUD::draw(Graphics &graphics)
{
	// Draw the EXP bar.
	lvl_label.draw(graphics);
	lvl_number.draw(graphics);
	exp_bar.draw(graphics);

	// Draw the HP bar.
	hp_bar.draw(graphics);
	hp_unit_digit.draw(graphics);
	current_hp.draw(graphics);

	// Draw the weapon info.
	slash_separator.draw(graphics);
	dash_placeholders.draw(graphics);
}

// Update the player HP.
void HUD::update(int elapsed_time)
{
	// Each digit is 8 pixels long, so multiply by 8.
	hp_unit_digit.setSourceX(8 * player->getCurrentHP());

	// Calculate the length of the HP bar. The full bar is 39 px long.
	float hp_percentage = (float)player->getCurrentHP() / player->getMaxHP();
	current_hp.setSourceWidth(std::floor(hp_percentage * 39));
}

