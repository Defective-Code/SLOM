#pragma once

#include <string>
#include <vector>
#include <set>

using namespace std;

class Hangman {

    const int MAX_STAGE = 7;

    std::set<char> seen_letters;
       
	public:
		void startGame();

	private:
		void display(int stage);

        std::vector<std::string> hangman_stages = {
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

        std::vector<std::string> flower_stages = {
             R"(
                 _
               _(_)_ 
              (_)@(_)
                (_)
                | |
              ======
             )",  // Full healthy flower

            R"(
                 _
               _(_)_ 
              (_)@(_)
                (_)
                | 
              ======
             )",  // One leaf missing

            R"(
                 _
               _(_)_ 
              (_)@(_)
                (_)
        
              ======
             )",  // No leaves

            R"(
                 _
               _(_)_ 
              (_)@(_)
        
      
              ======
             )",  // Flower stem only

            R"(
                 _
               _(_)_ 
        
        
      
              ======
             )",  // Just the upper part of the stem

            R"(
                 _
         
        
        
      
              ======
             )",  // Top of the stem gone

            R"(
         
         
        
        
      
              ======
            )"  // Completely wilted (game over)
        };


        


