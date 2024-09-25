#include "get_data.h"
#include "io_handler.h" //included here as all games require these methods


//This class defines the base structure of any game in this project. All games must have implementation for these methods
class Game {
public:
	virtual int startGame(); //this method returns the number of coins for hints.
	virtual void giveHint(); //function to present a hint to the user
private:
	virtual void display(); //this function displays the current game state
	virtual std::string generate(); //this function generates a string of the current game state, with the idea it is called by display(); This is for testing purpose
	virtual void menu(); //this fucntion should present a menu on the screen, and take in the user input to select the menu option. All games should have an option to guess (some games may have more than one such as hangman with guess a lettter and a word), a hint option, and a quit game option., 
};