
#pragma execution_character_set( "utf-8" )

#include <unordered_map>
#include <vector>


/**
 * @brief Clears the terminal screen.
 */
void clearScreen();

/**
 * @brief Splits a string into a vector of strings based on newline characters.
 *
 * @param input The input string to be split.
 * @return A vector of strings, each representing a line from the input.
 */
std::vector<std::string> splitStringOnNewline(const std::string& input);

/**
 * @brief Takes a single character input by the user and returns it in lowercase.
 *
 * @return The lowercase version of the user input character.
 */
char getSingleCharacter();

/**
 * @brief Takes a word input by the user and returns it in lowercase, removing any 
 * preceding whitespace and/or newline characters.
 *
 * @return The processed word in lowercase with leading whitespace and newlines removed.
 */
std::string getWord();

/**
 * @brief Clears the last n lines from the terminal screen.
 *
 * @param n The number of lines to clear.
 */
void clearLastNLines(int n);

/**
 * @brief Removes all whitespace from a given string.
 *
 * @param input The input string from which to remove whitespace.
 * @return The input string with all whitespace removed.
 */
std::string removeWhitespace(const std::string& input);

/**
 * @brief Converts a given string to lowercase.
 *
 * @param str The input string to be converted to lowercase.
 * @return The input string in lowercase.
 */
std::string toLowerCase(const std::string& str);
