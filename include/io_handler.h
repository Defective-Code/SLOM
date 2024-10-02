
#pragma execution_character_set( "utf-8" )

#include <unordered_map>
#include <vector>


void clearScreen();
/**
    * @brief Splits a string into a vector of strings based on newline characters.
    *
    * @param input The input string to be split.
    * @return A vector of strings, each representing a line from the input.
*/
std::vector<std::string> splitStringOnNewline(const std::string& input);

//This method takes in a single character input by the user, and returns it in lowercase.
char getSingleCharacter();

//This method takes in a word input by the user, and returns it in lower cases removing any preceeding whitespace and/or newline characters
std::string getWord();

void clearLastNLines(int n);

std::string removeWhitespace(const std::string& input);

std::string toLowerCase(const std::string& str);


