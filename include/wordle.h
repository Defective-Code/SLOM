#pragma once
#include <string>

class Wordle {
public:


	void initialiseGame();

	std::string selectWorldeWord();

	std::string receiveUserInput();

	void getNextGameState(const std::string userGuess);

	void displayGameState();

	void startGame();
};