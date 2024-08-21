#include <iostream> 
#include "input_handler.h"


// Declare a global variable
std::string wordleWord = "Test";
std::string displayWordleWord = "";
int attemptsLeft = 3;
bool wordleComplete = false;

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

std::string receiveUserInput(){
	std::string userInput;
	std::cin >> userInput;
	return userInput;
    // Code to get user key press
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
            // Correct character: color it gray
            displayWordleWord += "\033[38;5;8m" + std::string(1, guessChar) + "\033[0m ";
        } else if(wordleWord.find(guessChar)){
			// Checks if wordleWord contains letter (Note: needs updating to update displayWordleWord)
			std::cout << "Contains letter: " << guessChar << std::endl;
		}else{
            // Incorrect character: keep it as "_"
            displayWordleWord += "_ ";
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
