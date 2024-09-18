#pragma once

#include <string>
#include <vector>

class Hangman {

    std::vector<String>

    hangmen {"+ -- - +\n|   |\n        |\n        |\n        |\n        |\n        ======== = ",
        + -- - +
        |   |
        O   |
        |
        |
        |
        ======== = ''', '''
        + -- - +
        |   |
        O   |
        |   |
        |
        |
        ======== = ''', '''
        + -- - +
        |   |
        O   |
        /|   |
        |
        |
        ======== = ''', '''
        + -- - +
        |   |
        O   |
        /|\  |
        |
        |
        ======== = ''', '''
        + -- - +
        |   |
        O   |
        /|\  |
        /    |
        |
        ======== = ''', '''
        + -- - +
        |   |
        O   |
        /|\  |
        / \  |
        |
        ======== = '''};

	public:
		void startGame();

	private:
		void display();
};


