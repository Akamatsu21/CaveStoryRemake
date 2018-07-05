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
	hp_bar = Sprite(graphics, "..\\content\\sprites\\TextBox.png", 0, 40, 8, 64, 35, 70);
	hp_unit_digit = Sprite(graphics, "..\\content\\sprites\\TextBox.png", 0, 56, 8, 8, 66, 70);
}

// Draw all HUD elements.
void HUD::draw(Graphics &graphics)
{
	hp_bar.draw(graphics);
	hp_unit_digit.draw(graphics);
}

// Update the player HP.
void HUD::update(int elapsed_time)
{
	hp_unit_digit.setSourceX(8 * player->getCurrentHP());
}

