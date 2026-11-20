#include "Window.h"

Window::Window() { }

void Window::SetWindow(int width, int height)
{
	// This reassigns the values of our width & height variables
		//  to our passed width & height.
	this->width = width;
	this->height = height;


	HWND hwnd = GetConsoleWindow(); // Note: Technically depricated, but still functional.
	// GetWindow() will always fail if we run it immediately after the program is created.
	//   Sleep stops our program's execution for the passed number of milliseconds.
	Sleep(1);
	// In the Windows 11 virtual terminal, the console is a child of the terminal.
	//   In this case, we cannot resize the console and must instead resize the terminal.
	//   If there is no owner of the console (E.g. In Windows 10), then this will output 'NULL' (0).
	HWND owner = GetWindow(hwnd, GW_OWNER);

	// SetWindowPos allows us to reposition & resize our console window.
	//   By passing in the flags "" and "", we prevent our resizing from affecting the windows's position.
	//   This lets us only set the console's size (In pixels, hence the function calls).
	// The HWND that we need to pass in varies with the version of windows we are using,
	//   so we can use a ternary operator to use the correct one.
	//   If owner is null ? Windows 10 Specific : Windows 11 Specific.
	if (!SetWindowPos(owner == NULL ? hwnd : owner, nullptr, 0, 0, getPixelWidth(), getPixelHeight(), SWP_NOZORDER | SWP_NOMOVE))
	{
		// Note: As we are now clearing out console output every frame,
		//   this may get overriden before you can see it.
		//   Look into other ways of displaying errors, or for ways to stop the
		//   program temporarily (More on debugging in a later week).
		std::cout << "SetWindowPos failed with error: " << GetLastError() << std::endl;
	}

	// As its name implies, SetConsoleTitle changes the display name of the console.
	//   We are converting the string "TEST" into a wide character using the pre-string prefix 'L' (wchar_t)
	//   so that the function processes it properly.
	// When the programme is terminated, the console will revert to its original title.
	if (!SetConsoleTitle(L"TEST")) // Note: Technically depricated, but still functional.
	{
		// Note: As we are now clearing out console output every frame,
		//   this may get overriden before you can see it.
		//   Look into other ways of displaying errors, or for ways to stop the
		//   program temporarily (More on debugging in a later week).
		std::cout << "SetConsoleTitle failed with error: " << GetLastError() << std::endl;
	}


	// Hide the console cursor.
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = false; // Sets the console's cursor (What shows where you are typing) to be not visible.
	SetConsoleCursorInfo(out, &cursorInfo);
}
void Window::SetCursorPosition(int x, int y)
{
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	std::cout.flush(); // Forces the console to write any not-yet-written characters in its buffer.
	COORD coord = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(hOut, coord); // Note: Technically depricated, but still functional.
}