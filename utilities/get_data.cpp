#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include "get_data.h"

std::unordered_map<std::string, std::string> wordmap;
std::unordered_map<char, double> frequencymap;


DataGenerator::DataGenerator() {
	make_wordmap();
	calculate_relative_freqs();
}



void DataGenerator::make_wordmap() {
	std::cout << "Current working directory: " << std::filesystem::current_path() << "\n";

	std::ifstream file("../../../../../Data/MaoriWordsData.txt");

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
	std::cout << wordmap.bucket_count() << "\n";
}



std::pair<std::string, std::string> DataGenerator::get_random_entry(int length) {


	std::vector<std::pair<std::string, std::string>> matching_words;

	// Auto& makes it automatically detect the type, & makes it a reference to avoid copying
	for (const auto& keyvalue : wordmap) {
		std::cout << "Checking word: " << keyvalue.first << "\n";  // Debug line
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