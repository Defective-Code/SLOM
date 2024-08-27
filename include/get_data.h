#ifndef GET_DATA_H
#define GET_DATA_H

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <filesystem>


class DataGenerator {
public:
    std::unordered_map<std::string, std::string> wordmap;
    std::unordered_map<char, double> frequencymap;

    /***
    * Constructor calls method to instantiate our word map
    */
    DataGenerator();

	/***
     * Method to populate unordered map containing all Maori words and defnitions as key value pairs
     * Set up to handle multi line definitions
     * Key value pairs stored in wordmap
    */
    void make_wordmap();

    /***
     * Get random_entry method
     * Takes an optional length argument, finds all matching values that match that length and puts them into a vector
     * Randomly indexes the vector and returns the key value pair
     * Throws an error if no matching word found    
     *
     * @param length: Optional length of word, -1 by default for no length
     * @return returns randomly chosen word of given (or not) length
    */
    std::pair<std::string, std::string> get_random_entry(int length = -1);

    /***
     * Method to calculate relative frequencies of every letter used for data
     * Stores each frequency in a map frequencymap
     * Key: char
     * Value: the relative frequency of that letter
    */
    void calculate_relative_freqs();
};

#endif // GET_DATA_H
