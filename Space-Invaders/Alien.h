#pragma once
#include <iostream>
#include "GameObject.h"

class Alien : public GameObject
{
public:
	Alien();

	void Update() override;
	void Draw() override;


	void setActive(bool state);

private:
	bool isActive;
};