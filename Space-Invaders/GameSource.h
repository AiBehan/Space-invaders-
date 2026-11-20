// Ensures that this file is only ever included in each file it is referenced in once, no matter how many times its imported using '#include'.
#pragma once
// Tells the compiler to include specific header files while compiling the script, giving us access to them.
//   (In this case: iosteam & string from the C++ standard library).
#include <iostream>
#include <string>
// These includes reference other header files in our project, as opposed to standard C++ libraries.
#include "Window.h"
#include "Ground.h"
#include "Player.h"
#include "Alien.h"
#include "Barrier.h"
#include "ScreenBuffer.h"
#include "Menu.h"


#define GROUND_HEIGHT 29
#define PLAYER_HEIGHT 28
#define BARRIER_HEIGHT 22


class GameSource // Classes are the blueprint for Objects (Instances). (See main.cpp for how we've instantiated this class).
{
public: // 'public' variables and functions can be accessed by any class that has a reference to this (See main.cpp).
	GameSource(); // Default constructor.
	~GameSource(); // Destructor.

	void GameLoop();

private: // 'private' variables and functions can only be accessed within this class.
	bool m_runLoop = true;

	Window gameWindow;
	Ground gameGround;
	std::unique_ptr<Menu> m_menu = std::make_unique<Menu>(); // Smart Pointer.
	Player player;

	// As we haven't specified an initialisation (Here or in our constructor),
	//   these arrays will be comprised of instances initialised using their default
	//   constructor. (This is the same with our other class instances too, such as "player", "gameGround", etc).
	Alien aliens[20];		// Array of 20 alien instances.
	Barrier barriers[20];	// Array of 20 barrier instances.
	ScreenBuffer frontBuffer;
	ScreenBuffer backBuffer;
	ScreenBuffer resetBuffer;

	enum GameState
	{
		kStartScreen,
		kLevel1,
		kExit
	};

	GameState gS;



	// Our Initialisation Functions.
	void InitialiseGame();
	void CreateBuffers(int width, int height);
	void SetAlienPositions();
	void SetBarrierPositions();
	void SetPlayerPosition();

	// Our Update Functions.
	void ProcessInput();
	void UpdateGame();

	void SetGameState(int newState);

	// Our Rendering Functions.
	void DrawGame(int width, int height);
	void UpdateBuffer(int width, int height);
	void SwapBuffers();
};