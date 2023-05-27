#include<iostream>
#include<conio.h>

#include "InputHandler.h"
#include "nduc/Keycode.h"

int main() {
	while (true)
	{
		start();
		std::cout << "Press enter to continue... ";
		while (_getch() != KEY_ENTER);
		system("cls");
	}
}