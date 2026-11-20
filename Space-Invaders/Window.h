#pragma once
#include <iostream>
#include <windows.h>

class Window
{
public:
	Window();

	void SetWindow(int width, int height);
	void SetCursorPosition(int x, int y);

	int getWidth() { return this->width; }
	int getHeight() { return this->height; }

private:
	const int kCharacterPixelWidth = 10, kCharacterPixelHeight = 22; // Approximate pixel size of a character. We're aiming to overshoot, don't undershoot.
	int width, height;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	// These getters allow us to translate our width/height from character count into approximate pixel sizes.
	// The 'inline' keyword allows the compiler to replace the function's signature (Where you call it)
	//   with the function's definition (What it does)
	//   This can reduce overhead, but can be inefficient with larger functions, and it can reduce cache efficiency.
	//   They keyword is essentially a request. The compiler may or may not inline the function.
	inline int getPixelWidth() { return width * kCharacterPixelWidth; }
	inline int getPixelHeight() { return height * kCharacterPixelHeight; }
};