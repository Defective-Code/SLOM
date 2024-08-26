#ifndef GET_DATA_H
#define GET_DATA_H

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>

class DataGenerator {
public:
    std::unordered_map<std::string, std::string> wordmap;
    std::unordered_map<char, double> frequencymap;

    // Constructor
    DataGenerator();

    // Method to populate the wordmap
    void make_wordmap();

    // Method to get a random entry
    std::pair<std::string, std::string> get_random_entry(int length = -1);

    // Method to calculate relative frequencies
    void calculate_relative_freqs();
};

#endif // GET_DATA_H
