#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>
#include "get_data.h"
#include "wordfind.h"

int datagentest() {
	DataGenerator dg;

	std::pair < std::string, std::string> randword = dg.get_random_entry();
	std::cout << "Random word: " << randword.first << "\n";
	std::cout << "Definition: " << randword.second << "\n";
	return 0;
}