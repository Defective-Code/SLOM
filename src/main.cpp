﻿#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cstdio>
#ifdef _WIN32
#include <Windows.h>
#endif
#include "wordle.h"
#include "wordfind.h"
#include "hangman.h"
#include "wordmatchbingo.h"
#include "io_handler.h"

/***
 *	Method to render main menu to the console screen
*/
void displayMainMenu() {
	clearScreen();
	/*
	system("CLS"); //clear the terminal screen
	printf("Hi, welcome to SLOM, our application that has Maori twists on common word games.\n");
	printf("The following list is of the functions available to you, with the associated number to enter in before the brancket.\n");
	printf("To select an option, enter the corresponding letter and press enter, or to quit press q and then enter\n\n");
	printf("1) Wordle\n");
	printf("2) Wordfind\n");
	printf("3) Word Match Bingo\n");
	printf("4) Hangman\n\n");
	printf("Press q to quit\n\n");

	*/
	std::string menuText = R"(
	>>=========================<<
	|| ____  _     ___  __  __ ||
	||/ ___|| |   / _ \|  \/  |||
	||\___ \| |  | | | | |\/| |||
	|| ___) | |__| |_| | |  | |||
	|||____/|_____\___/|_|  |_|||
	>>=========================<<

	========================================
	🎉 WELCOME TO SLOM!🎉
	Your ultimate destination for Māori
	twists on classic word games!
	========================================

Are you ready to test your skills and have some fun ? 🌟

Here’s what we have in store for you :

1) Wordle				2) Wordfind
---------------------------------- -	---------------------------------- -
Can you guess the hidden word		Dive into a sea of letters and
in just six tries ? Use your wits	discover hidden words!Can you
and sharpen your vocabulary as you	find them all ?
uncover the mystery!

3) Word Match Bingo			4) Hangman
---------------------------------- -	---------------------------------- -
Match your words to their		Can you save the word from the
descriptions and fill your		gallows ? Guess the letters before
bingo card for a thrilling race		time runs out!
against the clock!

========================================
🚀 To make your selection, enter the
corresponding number and press Enter.
🛑 Press 'q' to quit anytime.
========================================

Let the games begin!🎮
)";
	
	std::cout << menuText << std::endl;


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

		// Get the first character from user input
		ch = getSingleCharacter();

		// Flush the remaining characters in the input buffer
		//while (getchar() != '\n');  // Discard all characters until a newline is encountered

		// Validate input: it must be a digit and within the desired range
	} while (ch != 'q' && (!isdigit(ch) || (ch - '0') <= 0 || (ch - '0') > range));

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
	//Wordscapes wordscapes = Wordscapes(15);
	WordMatchBingo wordmatchbingo = WordMatchBingo();
	Hangman hangman = Hangman();
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
		//case '3':
		//	wordscapes.runGame();
		//	break;
		case '3':
			wordmatchbingo.startGame();
			break;
		case '4':
			hangman.startGame();
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

	//printf("SLOM Started");
	printf("   ");

	#ifdef _WIN32
		SetConsoleOutputCP(CP_UTF8);
		setvbuf(stdout, nullptr, _IOFBF, 1000);
	#endif
	run();
    
	return 0;
}

