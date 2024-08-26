#include <stdio.h>
#include <stdlib.h>
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
	while (ch != 'q') {
		ch = getMenuOption(2);

		switch (ch) {
		case '1':
			Wordle::startGame();
			break;
		case '2':
			//Wordfind::startGame();
			break;
		case 'q':
			printf("Quitting.....");
			break;
		default:
			printf("Please select a valid option\n");
		}
	}
}


int main() {

	printf("SLOM Started");

	run();
    
	return 0;
}

