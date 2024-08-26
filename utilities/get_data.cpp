#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include "get_data.h"


    
    std::unordered_map<std::string, std::string> wordmap;

    std::unordered_map<std::string, std::string> getWordMap() {
        return wordmap;
    }


    /***
     * Method to populate unordered map containing all Maori words and defnitions as key value pairs
     * Set up to handle multi line definitions
     * Key value pairs stored in wordmap
    */
    void make_wordmap(){
        std::ifstream file("Data/MaoriWordsData.txt");

        // Check if file opened successfully
        if (!file.is_open()) {
            std::cerr << "Failed to open file." << std::endl;
            return;
        }

        // Iniitialise variables for iterating through file and instantiating our map 
        std::string line;
        std::string key;
        std::string definition;
        bool nextkey {true}; //this varaiable determines if the next line is a key (true = it is, false = the next line is a def)
        bool nextdef {false};
        bool addmap {false};



        while (std::getline(file, line)) {
            if (line.empty() || line[0] == '*') {
                if (!key.empty() && !definition.empty()) {
                    wordmap[key] = definition;
                }
                key.clear();
                definition.clear();
                nextkey = true;
            } else if (nextkey) {
                key = line;
                nextkey = false;
            } else {
                if (!definition.empty()) {
                    definition.append(" " + line);
                } else {
                    definition = line;
                }
            }
        }

        // Edge case where the last entry of the file does not end with a blank line or a '*'
        if (!key.empty() && !definition.empty()) {
            wordmap[key] = definition;
        }

        file.close();
    }


    /***
     * Get random_entry method
     * Takes an optional length argument, finds all matching values that match that length and puts them into a vector
     * Randomly indexes the vector and returns the key value pair
     * Throws an error if no matching word found
     * 
     * @param length: Optional length of word, -1 by default for no length
     * @return returns randomly chosen word of given (or not) length
    */
    std::pair<std::string, std::string> get_random_entry(int length = -1){
        

        std::vector<std::pair<std::string, std::string>> matching_words;

        // Auto& makes it automatically detect the type, & makes it a reference to avoid copying
        for (const auto& keyvalue : wordmap){
            if (length == -1  || keyvalue.first.length() == length) {
                matching_words.push_back(keyvalue);
            }
        }

        // Throw error if no matching words found 
        if (matching_words.empty()){
            throw std::runtime_error("No matching words found");
        }

        // Generate random number between 0 and length of matching_words vector
        int random_index = std::rand() % matching_words.size();
        return matching_words[random_index];

    }

    /***
     * Constructor calls method to instantiate our word map
    */
    DataGenerator() {
        make_wordmap();
    }


