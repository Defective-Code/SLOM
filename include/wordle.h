#pragma once
#include <string>

namespace Wordle {
	void initialiseGame();

	std::string selectWorldeWord();

	void receiveUserInput();

	void getNextGameState();

	void displayGameState();

	void startGame();
}