#pragma once
#pragma execution_character_set( "utf-8" )
#include <string>
#include <map>
#include "game.h"

/**
 * @class Wordle
 * @brief Represents a variant of the Wordle game where the player guesses a word by inputting guesses.
 * 
 * The class handles validating guesses, tracking attempts,
 * and providing hints. Inherits from the base class `Game`.
 */
class Wordle : private Game {
    /**
     * @brief Max number of attempts allowed in a game.
     */
    const static int MAX_ATTEMPTS = 5;

    /**
     * @brief Length of the word to be guessed in Wordle (always 5).
     */
    const int WORD_LENGTH = 5;

    /**
     * @brief The word that the user must guess to win the game.
     */
    std::string wordleWord = "Test";

    /**
     * @brief Display version of the wordle word with correct and incorrect guesses shown.
     */
    std::string displayWordleWord = "";

    /**
     * @brief Array holding the user's previous attempts in the game.
     */
    std::string attempts[MAX_ATTEMPTS];

    /**
     * @brief Map storing the count of each character in the wordleWord, used for validation.
     */
    std::map<char, int> charCount;

public:
    /**
     * @brief Starts the Wordle game.
     * 
     * This method is called when the user selects Wordle as their game of choice. It initializes 
     * the game setup and manages the game loop.
     * 
     * @return int Returns the status of the game (e.g., 0 if the game completes successfully).
     */
    int startGame() override;

private:
    /**
     * @brief Number of attempts the user has made so far.
     */
    int attemptsCount = 0;

    /**
     * @brief Boolean indicating whether the user has successfully guessed the word.
     */
    bool wordleComplete = false;

    /**
     * @brief The word the user must guess during the current session.
     */
    std::string wordToGuess;

    /**
     * @brief Definition of the word, could be used to give the user hints or additional context.
     */
    std::string wordDef;

    /**
     * @brief Provides a hint to the player during the game.
     * 
     * This method displays partial information about the word (first letter)
     */
    void giveHint() override;

    /**
     * @brief Receives input from the user for their Wordle guess.
     * 
     * This method collects input from the user and validates it to ensure it conforms 
     * to the expected word length.
     * 
     * @return std::string Returns the user's input guess.
     */
    std::string receiveUserInput();

    /**
     * @brief Updates the current game state based on the user's guess.
     * 
     * This method compares the user's guess to the correct word and updates the display
     * version of the word (showing correct letters in the correct positions).
     * 
     * @param userGuess A string containing the user's current guess.
     */
    void getNextGameState(const std::string userGuess);

    /**
     * @brief Sets up the game by initializing game variables and generating a word to guess.
     * 
     * This method is called before the game begins and prepares the word to be guessed, 
     * resets attempts, and initializes the game state.
     */
    void setup() override;

    /**
     * @brief Resets the game state to its initial configuration.
     * 
     * This method clears previous attempts, resets counters, and prepares for a new game.
     */
    void reset() override;

    /**
     * @brief Displays the game menu to the user.
     * 
     * This method shows the user the game options and allows them to choose an action.
     * 
     * @return bool Returns true if the user selects to play, false otherwise.
     */
    bool menu() override;

    /**
     * @brief Generates the word for the Wordle game.
     * 
     * This method picks or constructs a new word for the player to guess.
     * 
     * @return std::string The word that the user must guess.
     */
    std::string generate() override;

    /**
     * @brief Displays the current state of the game, including previous guesses.
     * 
     * This method renders the game's current state for the user, showing which letters 
     * have been guessed correctly and their positions.
     */
    void display() override;

    /**
     * @brief Friend class declaration allowing `WordleTest` to access private members.
     * 
     */
    friend class WordleTest;
};