#pragma once

#include <string>
#include <vector>
#include <set>

/**
 * @class Hangman
 * @brief The Hangman class encapsulates the logic and functionality for the Hangman game.
 */
class Hangman {

    /**
     * @brief Maximum number of incorrect guesses allowed before losing the game.
     */
    const int MAX_STAGE = 7;

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
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
        'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
        'U', 'V', 'W', 'X', 'Y', 'Z'
    };

    

    public:

        /**
         * @brief Starts the Hangman game.
         *
         * Initializes the game state and enters the game loop, allowing the player to guess letters or the entire word.
        */
        void startGame();

    private:
        /**
         * @brief Displays the current state of the game, including the hangman stage, used letters, and the word with guessed letters.
         *
         * @param stage The current stage of the hangman drawing, representing the number of incorrect guesses.
         */
        std::string display(int stage);

        /**
         * @brief Set of letters that have been guessed by the player.
         */
        std::set<char> seen_letters;

        /**
        * @brief Set of correctly guessed letters in the answer.
        */
        std::set<char> correct_letters;

        std::string word_input;

        char char_input;

        /**
         * @brief Splits a string into a vector of strings based on newline characters.
         *
         * @param input The input string to be split.
         * @return A vector of strings, each representing a line from the input.
         */
        std::vector<std::string> splitStringOnNewline(const std::string& input);

        /**
         * @brief Processes a letter guess by the player.
         *
         * @return True if the guessed letter is in the answer, otherwise false.
         */
        bool get_letter();

        /**
         * @brief Processes a word guess by the player.
         *
         * @return True if the guessed word matches the answer, otherwise false.
         */
        bool guess_word();
        
    friend class HangmanTest;
};
        


