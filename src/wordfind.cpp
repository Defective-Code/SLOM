#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>
#include "../include/get_data.h"

int datagentest() {
	DataGenerator dg;

	std::pair < std::string, std::string> randword = dg.get_random_entry();
	std::cout << "Random word: " << randword.first << "\n";
	std::cout << "Definition: " << randword.second << "\n";
	return 0;
}
namespace Wordfind {

}