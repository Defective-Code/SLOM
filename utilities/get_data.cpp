#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <ctime>
#include "get_data.h"

//std::unordered_map<std::string, std::string> wordmap;
//std::unordered_map<char, double> frequencymap;


DataGenerator::DataGenerator() {
	std::srand(static_cast<unsigned int>(std::time(0))); //explicit cast to avoid warning. Should be ok, but if the OS returns time as 64 bit this could lead to truncation.
	make_wordmap(DATA_FILE_PATH);
	calculate_relative_freqs();
}

DataGenerator::DataGenerator(std::string filepath) {
	std::srand(static_cast<unsigned int>(std::time(0))); //explicit cast to avoid warning. Should be ok, but if the OS returns time as 64 bit this could lead to truncation.
	make_wordmap(filepath);
	calculate_relative_freqs();
}



void DataGenerator::make_wordmap(std::string filepath) {

	//std::ifstream file("C:\\Users\\Liam\\University\\third-year\\second-sem\\COSC345\\SLOM\\Data\\MaoriWordsData.txt");
	std::ifstream file(filepath); //this filepath is defined in the CMakeLists.txt file in the utilities folder

	// Check if file opened successfully
	if (!file.is_open()) {
		std::cerr << "Failed to open file." << std::endl;
		return;
	}

	// Iniitialise variables for iterating through file and instantiating our map 
	std::string line;
	std::string key;
	std::string definition;
	bool nextkey{ true };
	bool nextdef{ false };
	bool addmap{ false };

	while (std::getline(file, line)) {
		
		if (line.empty() || line[0] == '*') {
			if (!key.empty() && !definition.empty()) {
				wordmap[key] = definition;
			}
			
			key.clear();
			definition.clear();
			nextkey = true;
		}
		else if (nextkey) {
			
			key = line;
			nextkey = false;
		}
		else {
			
			if (!definition.empty()) {
				definition.append(" " + line);
			}
			else {
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



std::pair<std::string, std::string> DataGenerator::get_random_entry(int length) {


	std::vector<std::pair<std::string, std::string>> matching_words;

	// Auto& makes it automatically detect the type, & makes it a reference to avoid copying
	for (const auto& keyvalue : wordmap) {
		// std::cout << "Checking word: " << keyvalue.first << "\n";  // Debug line
		if (length == -1 || keyvalue.first.length() == length) {
			matching_words.push_back(keyvalue);
		}
	}

	// Throw error if no matching words found 
	if (matching_words.empty()) {
		std::cerr << "No matching words found for length: " << length << "\n";  // Debug line
		throw std::runtime_error("No matching words found");
	}

	// Generate random number between 0 and length of matching_words vector
	int random_index = std::rand() % matching_words.size();
	return matching_words[random_index];

}

// Method to calculate relative letter frequency of every letter in class 
void DataGenerator::calculate_relative_freqs() {
	int total_letters = 0;

	for (const auto& keyvalue : wordmap) {
		const std::string& key = keyvalue.first;
		for (char ch : key) {
			total_letters++;
			frequencymap[ch]++;
		}
	}

	for (const auto& keyvalue : frequencymap) {
		frequencymap[keyvalue.first] = frequencymap[keyvalue.first] / total_letters;
	}
}

// Method to retrieve all words as a vector
std::vector<std::string> DataGenerator::get_all_words() {
	std::vector<std::string> all_words;
	
	for (const auto& keyvalue : wordmap) {
		all_words.push_back(keyvalue.first);
	}

	return all_words;
}

 // Method to get wordmap
std::unordered_map<std::string, std::string> DataGenerator::get_wordmap() {
	return wordmap;
}