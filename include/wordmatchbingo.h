#pragma once
#include <string>
#include <map>
#include <vector>
#include "game.h"

/**
 * @class WordMatchBingo
 * @brief Represents the Word Match Bingo game, where players match words to their definitions within a limited time.
 * 
 * The class handles tracking attempts, selecting bingo words, and providing hints.
 */
class WordMatchBingo {
    /**
     * @brief Max number of attempts allowed for the player.
     */
    const static int totalAttempts = 5;

    /**
     * @brief Total number of words in the bingo word pool.
     */
    int bingoWordPoolCount = 10;

    /**
     * @brief Total time (in seconds) allowed for guessing in the game.
     */
    std::int64_t totalTime = 60;

    /**
     * @brief Remaining time (in seconds) for the player to make guesses.
     */
    std::int64_t remainingTime = totalTime;

    /**
     * @brief The current word the player is attempting to guess.
     */
    std::string wordleWord = "Test";

    /**
     * @brief Display version of the wordle word with correct and incorrect guesses shown.
     */
    std::string displayWordleWord = "";

    /**
     * @brief Counter for the number of attempts the player has made so far.
     */
    int attemptsCount = 0;

    /**
     * @brief Counter for the number of words the player has found on their bingo card.
     */
    int wordsFound = 0;

    /**
     * @brief Total number of words on the bingo card.
     */
    int bingoCardCount = 10;

    /**
     * @brief Boolean to indicate whether the current word has been successfully guessed.
     */
    bool wordleComplete = false;

    /**
     * @brief Array to store the player's previous attempts in the game.
     */
    std::string attempts[totalAttempts];

    /**
     * @brief Map to store the frequency of each character in the word, used for validation.
     */
    std::map<char, int> charCount;

    /**
     * @brief The current word and its definition from the bingo card.
     * 
     * The pair contains the word and its corresponding definition.
     */
    std::pair<std::string, std::string> currentBingoWord = {"", ""};

    /**
     * @brief Stores the user's current guess for the bingo word.
     */
    std::string userGuess = "";

public:
    /**
     * @brief Starts the Word Match Bingo game.
     * 
     * Initializes the game setup, selects bingo words, and begins the game loop for the player.
     * 
     * @return int Returns the status of the game upon completion.
     */
    int startGame();

    /**
     * @brief Provides a hint to the player during the game.
     * 
     * This method may display partial information about the word or offer a clue to assist the player.
     */
    void getHint();

private:
    /**
     * @brief Vector storing the words and definitions on the player's bingo card.
     */
    std::vector<std::pair<std::string, std::string>> bingoCard;

    /**
     * @brief Vector storing the pool of available words and definitions from which the bingo card is generated.
     */
    std::vector<std::pair<std::string, std::string>> bingoCardPool;

    /**
     * @brief Selects the words and definitions to be placed on the player's bingo card.
     */
    void selectBingoCard();

    /**
     * @brief Receives input from the player for their guess.
     * 
     * This method collects the player's input and processes it for validation.
     */
    void receiveUserInput();

    /**
     * @brief Displays the current bingo card, showing the words and their statuses (whether found or not).
     */
    void displayBingoCard();

    /**
     * @brief Displays the current word from the bingo card that the player is attempting to match.
     */
    void displayCurrentBingoWord();

    /**
     * @brief Compares the user's input to the words on the bingo card.
     * 
     * @param userInput The player's current guess.
     * @return bool Returns true if the user's input matches a word on the bingo card, false otherwise.
     */
    bool compareUserInputToBingoCard(const std::string& userInput);

    /**
     * @brief Updates the word with a strikethrough once it has been found.
     * 
     * @param word The word to update with a strikethrough to indicate it has been guessed correctly.
     */
    void updateWordWithStrikethrough(std::string& word);

    /**
     * @brief Calculates the display length of a word, accounting for any special characters or formatting.
     * 
     * @param word The word whose display length is to be calculated.
     * @return size_t The length of the word as it would appear on the screen.
     */
    size_t getDisplayLength(const std::string& word);

    /**
     * @brief Resets the game state to its initial configuration.
     * 
     * This method clears the player's attempts, resets counters, and prepares for a new game session.
     */
    void reset();

    /**
     * @brief Sets up the initial game state, including generating the bingo word pool and selecting the bingo card.
     */
    void setup();

    /**
     * @brief Declares a friend class for testing purposes.
     */
    friend class WordMatchBingoTest;
};