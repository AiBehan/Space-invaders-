#pragma once
#include <iostream>
#include <windows.h> // Used for Input.
#include "GameObject.h"

class Player : public GameObject
{
public:
	Player();

	void Update();
	void Draw() override;
};