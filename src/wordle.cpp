#include <iostream> 
#include "input_handler.h"

// Declare a global variable

std::string wordleWord = "Test";
std::string displayWordleWord = "";
const int totalAttemps = 5;
int attemptsLeft = totalAttemps;
bool wordleComplete = false;
std::string attempts[totalAttemps];

std::string selectWorldeWord(){
    return "Holiday";
}

void displayGameState(){
    // Code to display game state
	std::cout << "\n" << displayWordleWord << std::endl;
}

void initialiseGame(){
    wordleWord = selectWorldeWord();
    // std::cout << "\nWordle word set to: " << wordleWord << std::endl;
    displayWordleWord = "";
    for (size_t i = 0; i < wordleWord.length(); ++i) {
        displayWordleWord += "_ ";
    }
	displayGameState();
}

std::string receiveUserInput() {
    std::string userInput;

    // Prompt user for input
    std::cout << "Enter a word with " << wordleWord.length() << " characters: ";
    
    while (true) {
        std::cin >> userInput;

        // Check if the length of the input matches the length of wordleWord
        if (userInput.length() == wordleWord.length()) {
            break; // Input is valid, exit the loop
        } else {
            std::cout << "Invalid input. Please enter a word with exactly " << wordleWord.length() << " characters: ";
        }
    }

    return userInput;
}

void getNextGameState(const std::string userGuess) {
    displayWordleWord = ""; // Reset the display string
	if(userGuess == wordleWord){
		wordleComplete = true;
	}
    for (size_t i = 0; i < userGuess.length(); ++i) {
        char guessChar = userGuess[i];
        char wordleChar = wordleWord[i];

        if (guessChar == wordleChar) {
            // Correct character -- colour it green
            displayWordleWord += "\033[38;5;10m" + std::string(1, guessChar) + "\033[0m ";
        } else if(wordleWord.find(guessChar) != std::string::npos){
			// Correct character by in wrong place -- Colour it yellow
			displayWordleWord += "\033[38;5;226m" + std::string(1, guessChar) + "\033[0m ";
		}else{
            // Incorrect character -- colour it gray
            displayWordleWord += "\033[38;5;250m" + std::string(1, guessChar) + "\033[0m ";
        }
    }
}

void startGame(){
	initialiseGame();
    while(attemptsLeft != 0 && !wordleComplete){
        getNextGameState(receiveUserInput());
		displayGameState();
        attemptsLeft -= 1;
    }
	if(wordleComplete){
		std::cout << "Congrats Wordle complete!" << std::endl;
	}else{
		std::cout << "You've ran out of attempts... better luck next time." << std::endl;
	}
}
