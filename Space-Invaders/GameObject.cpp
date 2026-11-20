#include "GameObject.h"


int GameObject::getXPos()
{
	return xPos;
}
void GameObject::setXPos(int newXPos)
{
	xPos = newXPos;
}

int GameObject::getYPos()
{
	return yPos;
}
void GameObject::setYPos(int newYPos)
{
	yPos = newYPos;
}

void GameObject::SetPosition(int newXPos, int newYPos)
{
	xPos = newXPos;
	yPos = newYPos;
}