#pragma once
#include <vector>
#include <string>
#include <unordered_map>

class DataGenerator {
public:
	void make_wordmap();
	std::pair<std::string, std::string> get_random_entry(int length = -1);
private:
	std::unordered_map<std::string, std::string> wordmap;
};