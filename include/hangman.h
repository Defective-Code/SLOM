#pragma once
#pragma execution_character_set( "utf-8" )

#include <string>
#include <vector>
#include <set>

#include <game.h> //extends this class

/**
 * @class Hangman
 * @brief The Hangman class encapsulates the logic and functionality for the Hangman game.
 */
class Hangman : private Game {

    /**
     * @brief Maximum number of incorrect guesses allowed before losing the game.
     */
    const int MAX_STAGE = 7;

    const int COIN_AMOUNT = 5;

    /**
     * @brief The word to be guessed by the player.
     */
    std::string answer;

    /**
     * @brief Vector of ASCII art representations of the hangman stages.
     */
    const std::vector<std::string> hangman_stages = {
            R"(                              
                   +---+      
                   |   |      
                       |      
                       |      
                       |      
                       |      
                =========     
                              )",

            R"(                              
                   +---+      
                   |   |      
                   O   |      
                       |      
                       |      
                       |      
                =========     
                             )",

            R"(                              
                   +---+      
                   |   |      
                   O   |      
                   |   |      
                       |      
                       |      
                =========     
                             )",

            R"(                              
                   +---+      
                   |   |      
                   O   |      
                  /|   |      
                       |      
                       |      
                =========     
                             )",

            R"(                              
                   +---+      
                   |   |      
                   O   |      
                  /|\  |      
                       |      
                       |      
                =========     
                             )",

            R"(                              
                   +---+      
                   |   |      
                   O   |      
                  /|\  |      
                  /    |      
                       |      
                =========     
                             )",

            R"(                              
                   +---+      
                   |   |      
                   O   |      
                  /|\  |      
                  / \  |      
                       |      
                =========     
                             )"
    };

    /**
     * @brief Vector of characters representing the English alphabet.
     */
    const std::vector<char> alphabet = {
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
    'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
    'u', 'v', 'w', 'x', 'y', 'z'
    };

    public:

        /**
         * @brief Starts the Hangman game.
         *
         * Initializes the game state and enters the game loop, allowing the player to guess letters or the entire word.
        */
        int startGame() override;

    private:
        /**
        * @brief Set of correctly guessed letters in the answer.
        */
        std::set<char> correct_letters;

        int current_stage; //tracks the current stage of the hangman game

        /**
         * @brief Set of letters that have been guessed by the player.
         */
        std::set<char> seen_letters;

        void giveHint() override;

        /**
         * @brief Displays the current state of the game, including the hangman stage, used letters, and the word with guessed letters.
         *
         * @param stage The current stage of the hangman drawing, representing the number of incorrect guesses.
         */
        void display() override;

        std::string generate() override;

        void setup() override; //this method sets up the games initial state, e.g initalize the word, setup background data sctructures etc.

        void reset() override;

        bool menu() override;

        bool checkGameEnd();

        /**
         * @brief Processes a letter guess by the player.
         *
         * @return True if the guessed letter is in the answer, otherwise false.
         */
        bool guessLetter(char input);

        /**
         * @brief Processes a word guess by the player.
         *
         * @return True if the guessed word matches the answer, otherwise false.
         */
        bool guessWord(std::string input);
        
    friend class HangmanTest;
};
        


