#include <iostream>
#include "get_data.h"
#include <cctype>
#include <string>
#include <map>
#include "wordle.h"
//#include "input_handler.h"

//Declare a global variable



//Function to check if a character is a diacritic
bool Wordle::isDiacritic(char32_t c) {
    if (c >= 0x0300 && c <= 0x036F) return true;
    if (c >= 0x1DC0 && c <= 0x1DFF) return true;
    //Latin Extended-A (includes macrons)
    if (c >= 0x0100 && c <= 0x017F) return true;
    return false;
}

//Function to check if the string contains any diacritic
bool Wordle::hasDiacritics(const std::string& input) {
    std::u32string utf32Str;

    //Convert UTF-8 string to UTF-32 to handle multi-byte characters
    for (size_t i = 0; i < input.size();) {
        char32_t c;
        unsigned char byte = input[i];
        if (byte < 0x80) {
            c = byte;
            ++i;
        }
        else if (byte < 0xE0) {
            c = (byte & 0x1F) << 6;
            c |= (input[++i] & 0x3F);
            ++i;
        }
        else if (byte < 0xF0) {
            c = (byte & 0x0F) << 12;
            c |= (input[++i] & 0x3F) << 6;
            c |= (input[++i] & 0x3F);
            ++i;
        }
        else {
            c = (byte & 0x07) << 18;
            c |= (input[++i] & 0x3F) << 12;
            c |= (input[++i] & 0x3F) << 6;
            c |= (input[++i] & 0x3F);
            ++i;
        }
        utf32Str += c;
    }

    //Check each character in the string
    for (char32_t c : utf32Str) {
        if (isDiacritic(c)) {
            return true;
        }
    }

    return false;
}

std::string Wordle::selectWordleWord() {
	printf("Welcome to Wordle!\n");
    DataGenerator generator;
    std::string result;

    
    do {
        auto entry = generator.get_random_entry();
        result = entry.first;
        //result = "toru";
        printf("%s\n", result.c_str());
        
    } while (hasDiacritics(result));
    
    return result.substr(0, result.length() - 1);
    //return result;
}


void clearLastNLines(int n)
{
	for (int i = 0; i < n; ++i)
	{
		//Move cursor up one line and clear the line
		std::cout << "\033[A\033[2K";
	}
}

void Wordle::displayGameState()
{
	for (size_t i = 0; i < totalAttempts; ++i)
	{
		std::cout << attempts[i] << std::endl;
	}
}

void Wordle::initialiseGame()
{
	wordleWord = selectWordleWord();
	//std::cout << "\nWordle word set to: " << wordleWord << std::endl;
	displayWordleWord = "";
	for (size_t i = 0; i < wordleWord.length(); ++i)
	{
		displayWordleWord += "_ ";
	}
	for (size_t i = 0; i < totalAttempts; ++i)
	{
		attempts[i] = displayWordleWord;
	}
	displayGameState();
}

std::string Wordle::receiveUserInput()
{
	std::string userInput;
	int lastWasError = false;

	//Prompt user for input
	std::cout << "Enter a word with " << wordleWord.length() << " characters: ";

	while (true)
	{
		std::cin >> userInput;

		//Check if the length of the input matches the length of wordleWord
		if (userInput.length() == wordleWord.length())
		{
			if(lastWasError){
				clearLastNLines(1);
			}
				
			break; //Input is valid, exit the loop
		}
		else
		{
			std::cout << "Invalid input. Please enter a word with exactly " << wordleWord.length() << " characters: ";
			lastWasError = true;
		}
	}

	return userInput;
}

void Wordle::getNextGameState(const std::string userGuess){
    displayWordleWord = ""; //Reset the display string
    std::string tempWordleWord = wordleWord; //Copy of the wordleWord to mark characters as used
    std::string result(userGuess.length(), ' '); //Placeholder for final result

    if (userGuess == wordleWord)
    {
        wordleComplete = true;
    }

    //First pass: check for correct positions (green)
    for (size_t i = 0; i < userGuess.length(); ++i)
    {
        char guessChar = std::tolower(userGuess[i]);
        char wordleChar = std::tolower(wordleWord[i]);

        if (guessChar == wordleChar)
        {
            //Correct character -- color it green
            result[i] = 'G';
            tempWordleWord[i] = '*'; //Mark this character as used
        }
    }

    //Second pass: check for correct characters in wrong positions (yellow)
    for (size_t i = 0; i < userGuess.length(); ++i)
    {
        if (result[i] == 'G') //Skip already colored characters
            continue;

        char guessChar = std::tolower(userGuess[i]);
        size_t pos = tempWordleWord.find(guessChar);

        if (pos != std::string::npos)
        {
            //Correct character in wrong place -- color it yellow
            result[i] = 'Y';
            tempWordleWord[pos] = '*'; //Mark this character as used
        }
        else
        {
            //Incorrect character -- color it gray
            result[i] = 'X';
        }
    }

    //Build the displayWordleWord string based on the result
    for (size_t i = 0; i < result.length(); ++i)
    {
        char guessChar = std::tolower(userGuess[i]);

        if (result[i] == 'G')
        {
            displayWordleWord += "\033[38;5;10m" + std::string(1, guessChar) + "\033[0m ";
        }
        else if (result[i] == 'Y')
        {
            displayWordleWord += "\033[38;5;226m" + std::string(1, guessChar) + "\033[0m ";
        }
        else
        {
            displayWordleWord += "\033[38;5;250m" + std::string(1, guessChar) + "\033[0m ";
        }
    }

    attempts[attemptsCount] = displayWordleWord;
    attemptsCount += 1;
}




void Wordle::startGame()
{
	clearLastNLines(11);
	initialiseGame();
	while (attemptsCount != totalAttempts && !wordleComplete)
	{
		getNextGameState(receiveUserInput());
		clearLastNLines(6);
		displayGameState();
	}
	if (wordleComplete)
	{
		std::cout << "Congrats Wordle complete!" << std::endl;
	}
	else
	{
		std::cout << "You've ran out of attempts... better luck next time." << std::endl;
	}
}