#include "Player.h"

Player::Player()
{
	// Two-stage Initialisation (Less efficient, less readable, and can lead to undefined behaviour. Review Wk4 Labs).
	this->xPos = 10;
}


void Player::Update()
{
	// We can pass in a character which will be automatically converted to its ASCII/virtual key-code.
	//   This character must be the capitalised version of what is on the keyboard (E.g. ‘W’ not ‘w’).
	if (GetKeyState('A') & 0x8000)
	{
		// Move the player left.
		if (xPos > 0) // Ensure that we never move off screen.
		{
			setXPos(xPos - 1);
		}
	}
	if (GetKeyState('D') & 0x8000)
	{
		// Move the player right.
		if (xPos < 79) // Ensure that we never move off screen.
		{
			setXPos(xPos + 1);
		}
	}
}
void Player::Draw()
{
	std::cout << "^";
}