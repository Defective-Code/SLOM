#include "get_data.h"
#include "io_handler.h" //included here as all games require these methods


//This pure abstract class defines the base structure of any game in this project. All games must have implementation for these methods
class Game {
public:
	virtual int startGame() = 0; //this method returns the number of coins for hints. All this method should do is call other methods within the class that actually do game and menu logic
	virtual void giveHint() = 0; //function to present a hint to the user
private:
	virtual void display() = 0; //this function displays the current game state. This method should contain any display code that doesn't go in the menu generate() method, e.g clear() the terminal screen.
	virtual std::string generate() = 0; //this function generates a string of the current game state, with the idea it is called by display(); This is for testing purpose
	virtual void setup() = 0; //method that sets up a games initial state
	virtual void reset() = 0; //method to reset the state of the game
	virtual void menu() = 0; //this fucntion should present a menu on the screen, and take in the user input to select the menu option. All games should have an option to guess (some games may have more than one such as hangman with guess a lettter and a word), a hint option, and a quit game option., 
};