#pragma once


class GameObject
{
public:
	GameObject() {};

	virtual void Update() {};
	virtual void Draw() = 0;


	int getXPos();
	void setXPos(int newXPos);
	int getYPos();
	void setYPos(int newYPos);

	void SetPosition(int newXPos, int newYPos);

protected:
	int xPos;
	int yPos;
};