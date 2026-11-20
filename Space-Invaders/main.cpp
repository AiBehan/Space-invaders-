// Tells the compiler to include specific header files while compiling the script, giving us access to them.
//   (In this case: the 'GameSource.h' file so that we can access the GameSource class).
#include "GameSource.h"


// The 'main()' function is the entry point for our program.
//   Typically, we have it return an integer so that we can display error codes.
//   When this function reaches its end, the program has finished executing.
int main()
{
	GameSource game; // Create an instance of 'GameSource' and store it in the variable 'game' (Variables are covered more in Wk2).
	game.GameLoop(); // Run the public function 'GameLoop()' within the instance of GameSource we've just created.

	return 0; // Whatever you return here will be the exit code displayed when the program stops running.
}