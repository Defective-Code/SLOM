#include "get_data.h"
#include "io_handler.h" // Included here as all games require these methods

#pragma once

#pragma execution_character_set( "utf-8" )

/**
 * This pure abstract class defines the base structure of any game in this project. 
 * All games must have an implementation for these methods.
 */
class Game {
public:
    /**
     * Starts the game and returns the number of coins for hints.
     * All this method should do is call other methods within the class that handle 
     * game and menu logic.
     * 
     * @return The number of coins available for hints.
     */
    virtual int startGame() = 0;

private:
    /**
     * Presents a hint to the user.
     */
    virtual void giveHint() = 0;

    /**
     * Displays the current game state.
     * This method should contain any display code that doesn't go in the 
     * menu generate() method, for example, clearing the terminal screen.
     */
    virtual void display() = 0;

    /**
     * Generates a string representing the current game state. 
     * This is for testing purposes and should be called by display().
     * 
     * @return A string representing the current game state.
     */
    virtual std::string generate() = 0;

    /**
     * Sets up the game's initial state.
     */
    virtual void setup() = 0;

    /**
     * Resets the state of the game.
     */
    virtual void reset() = 0;

    /**
     * Presents a menu on the screen and handles user input for menu selection.
     * All games should have options to guess (some games may have more than one, 
     * such as Hangman, where there are options to guess a letter or a word), 
     * request a hint, and quit the game.
     * 
     * @return A boolean indicating whether the menu was handled successfully.
     */
    virtual bool menu() = 0;
};
