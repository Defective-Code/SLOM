#include <iostream>
#include "input_handler.h"
#include <string>

// Declare a global variable
std::string wordleWord = "Test";
std::string displayWordleWord = "";
int attemptsLeft = 5;
bool wordleComplete = false;

std::string selectWorldeWord(){
    return "Wordle";
}

void initialiseGame(){
    wordleWord = selectWorldeWord();
    std::cout << "\nWordle word set to: " << wordleWord << std::endl;
    displayWordleWord = "";
    for (size_t i = 0; i < wordleWord.length(); ++i) {
        displayWordleWord += "_ ";
    }
	std::cout << "\nCurrent display for Wordle word set: " << displayWordleWord << std::endl;
}

std::string receiveUserInput(){
	return "Hurdle";
    // Code to get user key press
}

void getNextGameState(const std::string userGuess){
    for (size_t i = 0; i < userGuess.length(); ++i) {
        char guessChar = userGuess[i];
        char wordleChar = wordleWord[i];

        if(guessChar == wordleChar){
            displayWordleWord[i * 2] = guessChar;
        }
    }
    std::cout << "Updated: " << displayWordleWord << std::endl;
}

void displayGameState(){
    // Code to display game state
}

void startGame(){
	initialiseGame();
    while(attemptsLeft != 0 && !wordleComplete){
        getNextGameState(receiveUserInput());
		displayGameState();
        attemptsLeft = 0;
    }
}
