#include <stdio.h>
#include <iostream> 

#include "hangman.h"


void Hangman::display() {
	std::cout << "O\n---\n|\n" << "/\\" << std::endl;
}

void Hangman::startGame() {
	display();

	int x;
	std::cin >> x; // Get user input from the keyboard
}