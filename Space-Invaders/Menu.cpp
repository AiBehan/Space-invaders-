#include "Menu.h"

extern int menuChoice = 0; // Extern example to share data with menu and gameSource.

Menu::Menu() {}
Menu::~Menu() {}

void Menu::run()
{
	bool isValid = false;
	int choice;

	do
	{
		// Clear the screen.
		system("cls");

		// Display options.
		std::cout << "Start Screen:" << std::endl;
		std::cout << "1. Play Space Invaders" << std::endl;
		std::cout << "2. Quit" << std::endl;
		std::cout << "Enter your choice: ";
		std::cin >> choice;

		switch (choice)
		{
		case 1:
			menuChoice = 1;
			isValid = true;
			system("cls");
			break;
		case 2:
			menuChoice = 2;
			isValid = true;
			system("cls");
			break;

		default:
			std::cout << "Invalid choice. Please try again." << std::endl;
		}

		if (!isValid)
		{
			std::cout << "Press any key to continue..." << std::endl;
			_getch(); // Wait for user to press any key.
		}
	} while (!isValid);
}