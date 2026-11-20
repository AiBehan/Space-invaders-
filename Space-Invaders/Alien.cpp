#include "Alien.h"

// Constructor Initialisation List.
// By following our constructor with ": GameObject()" means that we will also utilise GameObject's
//   default constructor when calling Alien's default constructor.
Alien::Alien() : GameObject(),
	isActive(true)
{ }


void Alien::Update() { }
void Alien::Draw()
{
	std::cout << "A";
}


void Alien::setActive(bool state)
{
	this->isActive = state;
}