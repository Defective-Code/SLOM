#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cstdio>
#ifdef _WIN32
#include <Windows.h>
#endif
#include "wordle.h"
#include "wordfind.h"

/***
 *	Method to render main menu to the console screen
*/
void displayMainMenu() {
	system("CLS"); //clear the terminal screen
	printf("Hi, welcome to SLOM, our application that has Maori twists on common word games.\n");
	printf("The following list is of the functions available to you, with the associated number to enter in before the brancket.\n");
	printf("To select an option, enter the corresponding letter and press enter, or to quit press q and then enter\n\n");
	printf("1) Wordle\n");
	printf("2) Wordfind\n\n");
	printf("Press q to quit\n\n");
	//printf("\u001b[31mQ\u001b[0m");
}

/***
 * Method that captures the user next keypress, for selecting the option in the menu. Loops until a valid option is chosen
 * @param the integer value attached to the last menu option.
 * return the char that is attached to the menu option the user selects
*/
char getMenuOption(int range) {
	char ch;
	
	do {
		displayMainMenu();
		ch = getchar();
	} while (ch != 'q' && !isdigit(ch) && ((ch - '0') <= 0 || (ch - '0') > range)); //this checks if the entered character is a digit, and within the range of menu item values, subtracting '0' as that returns converts the number from its ASCII value to its actual value
	return ch;
}

/***
* Function to start the application. Displays the main menu, and handles the user input in the menu
*/
void run() {
	char ch = '0'; //variable to store user input
	//Wordle::startGame();
	Wordle wordle = Wordle();
	Wordfind wordfind = Wordfind();
	while (true) {
		displayMainMenu();
		std::cin >> ch;

		switch (ch) {
		case '1':
			wordle.startGame();
			break;
		case '2':
			wordfind.startGame();
			break;
		case 'q':
			printf("Quitting.....");
			return;
		default:
			printf("Please select a valid option\n");
		}
	}
	std::cout << std::endl; // Print a blank line for readability
}


int main() {

	printf("SLOM Started");

	#ifdef _WIN32
		SetConsoleOutputCP(CP_UTF8);
		setvbuf(stdout, nullptr, _IOFBF, 1000);
	#endif
	run();
    
	return 0;
}

