// We only need to include the "GameSource" header file here, as it contains all the includes we require.
#include "GameSource.h"

extern int menuChoice;

GameSource::GameSource()
{

}
GameSource::~GameSource()
{

}


// We need to prepend "GameSource::" to our GameLoop identifier to access
//   our declaration as it is only within the scope of the GameSource class
//   (Which isn't this .cpp file).
void GameSource::GameLoop()
{
	InitialiseGame();

	// This loop will run until 'm_runLoop' is set to false.
	// As we're not artificially limiting how often this loop runs, it will repeat itself as soon as it finishes executing.
	//   This means that the functions can run thousands or tens-of-thousands of times a second
	//   (Hence why the console almost immediately maxes out on the number of lines it can display).
	while (gS != GameState::kExit)
	{
		switch (gS)
		{
		case GameState::kStartScreen:
			m_menu->run();
			SetGameState(menuChoice);
			break;
		case GameState::kLevel1:
			ProcessInput();
			UpdateGame();
			UpdateBuffer(gameWindow.getWidth(), gameWindow.getHeight());
			SwapBuffers();
			DrawGame(gameWindow.getWidth(), gameWindow.getHeight());
			break;
		}
	}
};


// ----- Initialisation Functions -----

void GameSource::InitialiseGame()
{
	gameWindow.SetWindow(80, 30);
	CreateBuffers(80, 30);
	SetAlienPositions();
	SetBarrierPositions();
	SetPlayerPosition();

	gS = GameState::kStartScreen;
}
void GameSource::CreateBuffers(int width, int height)
{
	// Create our buffers.
	frontBuffer = ScreenBuffer(width, height);
	backBuffer = ScreenBuffer(width, height);
	resetBuffer = ScreenBuffer(width, height);

	// Initialise our buffers.
	for (int x = 0; x < width; ++x)
	{
		for (int y = 0; y < height; ++y)
		{
			resetBuffer.setChar(x, y, ' ');
		}
	}

	frontBuffer = resetBuffer;
	backBuffer = resetBuffer;
}
void GameSource::SetAlienPositions()
{
	// Spawn our aliens at their initial positions
	//   (Each will have a 2 gap between them).
	for (int x = 0; x < 20; ++x)
	{
		// We are accessing the alien at index 'x' in our aliens array
		//   (E.g. Alien[0] is the first, Alien[19] is the last).
		aliens[x].SetPosition(x * 3, 1);
	}
}
void GameSource::SetBarrierPositions()
{
	// Create all our barriers at our desired positions.
	for (int i = 0; i < 5; ++i)
	{
		barriers[i].SetPosition(i + 10, BARRIER_HEIGHT);
	}
	for (int i = 5; i < 10; ++i)
	{
		barriers[i].SetPosition(i + 25, BARRIER_HEIGHT);
	}
	for (int i = 10; i < 15; ++i)
	{
		barriers[i].SetPosition(i + 40, BARRIER_HEIGHT);
	}
	for (int i = 15; i < 20; ++i)
	{
		barriers[i].SetPosition(i + 55, BARRIER_HEIGHT);
	}
}
void GameSource::SetPlayerPosition()
{
	player.SetPosition(0, PLAYER_HEIGHT);
}


// ----- Update Functions -----

void GameSource::ProcessInput()
{
	player.Update();
}
void GameSource::UpdateGame()
{

}

void GameSource::SetGameState(int newState)
{
	gS = static_cast<GameState>(newState); // Static Casting.
}


// ----- Rendering Functions -----
void GameSource::DrawGame(int width, int height)
{
	// Using our ScreenBuffer, draw to the screen.
	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			gameWindow.SetCursorPosition(x, y);
			std::cout << frontBuffer.getChar(x, y);
		}
	}
}
void GameSource::UpdateBuffer(int width, int height)
{
	for (int y = 0; y < height; ++y)
	{
		// Draw in each column (In each x position).
		for (int x = 0; x < width; ++x)
		{
			bool hasDrawnToScreen = false;

			// Try to draw an alien at this position.
			for (int alienIndex = 0; alienIndex < 20; ++alienIndex)
			{
				if (aliens[alienIndex].getYPos() == y && aliens[alienIndex].getXPos() == x)
				{
					backBuffer.setChar(aliens[alienIndex].getXPos(), aliens[alienIndex].getYPos(), 'A');
					hasDrawnToScreen = true;
				}
			}

			// Try to draw a Barrier.
			if (y == BARRIER_HEIGHT)
			{
				// Try to draw an alien at this position.
				for (int barrierIndex = 0; barrierIndex < 20; ++barrierIndex)
				{
					if (barriers[barrierIndex].getXPos() == x)
					{
						backBuffer.setChar(barriers[barrierIndex].getXPos(), BARRIER_HEIGHT, '=');
						hasDrawnToScreen = true;
					}
				}
			}

			// Try to draw the Player.
			else if (y == PLAYER_HEIGHT)
			{
				if (x == player.getXPos())
				{
					backBuffer.setChar(player.getXPos(), PLAYER_HEIGHT, '^');
					hasDrawnToScreen = true;
				}
			}

			// Try to draw the Ground.
			else if (y == GROUND_HEIGHT)
			{
				backBuffer.setChar(x, GROUND_HEIGHT, '_');
				hasDrawnToScreen = true;
			}


			// As we're resetting our buffer before our loop,
			//   we no longer need to set blank spaces within our loop.
			/*if (!hasDrawnToScreen)
			{
				backBuffer.setChar(x, y, ' ');
			}*/
		}
	}
}
void GameSource::SwapBuffers()
{
	// This is not an efficient method of swapping & resetting our buffers.
	// Every frame, we're copying width*height*2 integers.
	// How could you make this more performant/better? If you manage to, that's marks for the Coursework.
	frontBuffer = backBuffer;
	backBuffer = resetBuffer;
}