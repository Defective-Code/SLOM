﻿#include <iostream>
#include <cctype>
#include <string>
#include <map>
#include <algorithm>
#include <thread>
#include <sstream>

#include "io_handler.h"
#include "wordle.h"
#include "get_data.h"

void Wordle::reset(){
    //Reset global variables
    wordleWord = "Test"; //Or any default word, if applicable
    displayWordleWord = "";
    attemptsCount = 0;
    wordleComplete = false;

    //Clear the attempts array
    for (int i = 0; i < MAX_ATTEMPTS; ++i) {
        attempts[i] = std::string(wordleWord.length() * 2, '_'); //Adjust based on your display format
    }

    //Clear the character count map if necessary
    charCount.clear();
}

std::string Wordle::generate() {
    std::ostringstream oss;
    
    oss << R"(
+======================================+
|   __        __            _ _        |
|   \ \      / /__  _ __ __| | | ___   |
|    \ \ /\ / / _ \| '__/ _` | |/ _ \  |
|     \ V  V / (_) | | | (_| | |  __/  |
|      \_/\_/ \___/|_|  \__,_|_|\___|  |
|                                      |
+======================================+
)" << std::endl;

    for (size_t i = 0; i < MAX_ATTEMPTS; ++i)
	{
		oss << attempts[i] << std::endl;
	}

    oss << "Press 1) to guess a word\nPress q to quit" << std::endl;

    return oss.str();
}

void Wordle::display() {
    clearScreen();

    std::cout << generate() << std::endl;
}

bool Wordle::menu() {
    char ch = getSingleCharacter();
    switch (ch) {
    case '1':
    {
        std::string input = receiveUserInput();
        getNextGameState(input);
        break;
    }
    case 'q':
    {
        std::cout << "Quitting.....\n";
        return false;
    }
    default:
        std::cout << "Please select a valid option\n";
    }
    return true;
}

std::string Wordle::receiveUserInput()
{
	std::string userInput = "test";
	int lastWasError = false;

	//Prompt user for input
	std::cout << "Enter a word with " << wordleWord.length() << " characters: ";

	while (true)
	{
		userInput = getWord();

		//Check if the length of the input matches the length of wordleWord
		if (userInput.length() == wordleWord.length())
		{
			if(lastWasError){
				clearLastNLines(1); //clear the user entered word if the input doesn't match the required number of characters
			}
				
			break; //Input is valid, exit the loop
		}
		else
		{
            if(lastWasError){
				clearLastNLines(1);
			}
			std::cout << "Invalid input. Please enter a word with exactly " << wordleWord.length() << " characters: ";
			lastWasError = true;
		}
	}
    //std::cout << userInput << std::endl;
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
            //Correct char -- color it green
            result[i] = 'G';
            tempWordleWord[i] = '*'; //Mark this character as used
        }
    }

    //Second pass: check for correct characters in wrong positions (yellow)
    for (size_t i = 0; i < userGuess.length(); ++i)
    {
        if (result[i] == 'G') //Skip already coloured characters
            continue;

        char guessChar = std::tolower(userGuess[i]);
        size_t pos = tempWordleWord.find(guessChar);

        if (pos != std::string::npos)
        {
            //Correct char, in wrong place -- colour it yellow
            result[i] = 'Y';
            tempWordleWord[pos] = '*'; //Mark this char as used
        }
        else
        {
            //Incorrect char -- colour it grey
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

    //std::cout << displayWordleWord << std::endl;

    attempts[attemptsCount] = displayWordleWord;
    attemptsCount += 1;
}

void Wordle::setup() {
    DataGenerator generator;

    //std::string test = "rūma";

    //std::cout << utf8Length(test) << std::endl;
    
    wordToGuess = "";
    //get a word and loop until the word is of the correct length
    while (wordToGuess.length() != WORD_LENGTH) {
        auto wordPair = generator.get_random_entry();
        wordToGuess = removeWhitespace(wordPair.first);
        wordDef = wordPair.second;
    }
    //wordToGuess = removeWhitespace(wordToGuess);

    wordleWord = wordToGuess;

    std::cout << wordToGuess.c_str() << std::endl;
    //printf("%zu\n", result.length());

    //this code initializes the initial state of the display word (e.g the _ initially displayed)
    displayWordleWord = "";
	for (size_t i = 0; i < wordleWord.length(); ++i)
	{
		displayWordleWord += "_ ";
	}
	for (size_t i = 0; i < MAX_ATTEMPTS; ++i)
	{
		attempts[i] = displayWordleWord;
	}
}

void Wordle::giveHint() {
    
}

int Wordle::startGame() {

	setup();
	while (attemptsCount != MAX_ATTEMPTS && !wordleComplete)
	{
		display();
        if (menu() == false) return 0;
	}
	if (wordleComplete)
	{   
        std::cout << "Word : " << wordleWord << " | Definition : " << wordDef << std::endl;
		std::cout << "Congrats Wordle complete!" << std::endl;
        display(); //display the completed wordle
	}
	else
	{
		std::cout << "You've ran out of attempts... better luck next time." << std::endl;
	}

    std::this_thread::sleep_for(std::chrono::seconds(3));
    reset();

    return 0;
}