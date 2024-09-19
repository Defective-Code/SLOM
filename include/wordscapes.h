#ifndef WORDSCAPES_H
#define WORDSCAPES_H

#include <vector>
#include <string>
#include <unordered_map>
#include "get_data.h"

/**
 * @brief A map containing words as keys and their definitions as values.
 */
extern std::unordered_map<std::string, std::string> wordmap;


/**
 * @class Wordscapes
 * @brief A class that generates a crossword-style grid game similar to Wordscapes.
 */
class Wordscapes {
private:
    /**
     * @brief The crossword grid, represented as a 2D vector of characters.
     */
    std::vector<std::vector<char>> crossword;


    /**
     * @brief The subset of letters that the player can use to form words.
     */
    std::vector<char> letterSubset;

    /**
     * @brief An instance of the DataGenerator class used to load word data from a file.
     */
    DataGenerator dg;

    /**
     * @brief Selects a random subset of letters from a predefined set.
     *
     * @param numLetters The number of letters to select for the subset.
     */
    void selectRandomLetters(int numLetters);

    /**
     * @brief Checks if the given word can be formed using the current subset of letters.
     *
     * @param word The word to be checked for validity.
     * @return true If the word can be formed using the letter subset.
     * @return false If the word cannot be formed using the letter subset.
     */
    bool isValid(const std::string& word);

    /**
     * @brief Generates the crossword grid by placing valid words from the word map.
     */
    void makeCrossword();

public:
    /**
     * @brief Constructor that initializes the crossword grid with the given size.
     *
     * @param size The size of the crossword grid (both width and height).
     */
    Wordscapes(int size);

    /**
     * @brief Removes macrons from characters, converting them to their non-diacritic equivalent.
     *
     * @param c The character to be normalized.
     * @return char The character with the macron removed, or the original character if no macron is present.
     */
    char removeMacron(char c);

    /***
    * @ brief Method to place first word, centred in grid
    * 
    * @param word to plac
    */
    void placeFirstWord(const std::string& word);

    /***
    * @brief Method to place word horizontally
    * 
    * @param word to place
    */
    bool placeWordHorizontally(const std::string& word);

    bool canIntersect(const std::string& word, bool& isHorizontal, int& row, int& col);

    bool Wordscapes::placeWordWithIntersection(const std::string& word);

    /***
    * @brief Method to place word vertically
    *
    * @param word to place
    */
    bool placeWordVertically(const std::string& word);


    /**
     * @brief Converts a word to its normalized form by removing diacritics (such as macrons).
     *
     * @param word The word to be normalized.
     * @return std::string The normalized word without diacritics.
     */
    std::string convertWord(const std::string& word);

    /**
     * @brief Displays the current crossword grid on the console.
     */
    void displayCrossword();

    /**
     * @brief Runs the game, generating the crossword and displaying it.
     */
    void runGame();
};

#endif // WORDSCAPES_H
