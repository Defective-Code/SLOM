#include "get_data.h"
#include <stdio.h>
#include <string>
#include <cassert>
#include <type_traits>

void make_wordmap_t() {
	//Testing if key contains multiple space seperated words
	std::string filepath = TEST_RESOURCES_FILE_PATH + std::string("test_data.txt");
	std::cout << filepath << std::endl;
	DataGenerator dg_test = DataGenerator(filepath);

	std::cout << dg_test.wordmap.size() << std::endl;

	std::cout << dg_test.wordmap["hello"] << std::endl;
	assert(dg_test.wordmap["hello"] == "a standard greeting in the English language");
	assert(dg_test.wordmap["world"] == "meaning either the earth, together with all of its countries and peoples or a particular region or group of countries");
	assert(dg_test.wordmap.size() == 3);

	assert(dg_test.wordmap.find("hellos") == dg_test.wordmap.end());

	assert(dg_test.wordmap["multiline"].compare("a test of multiline definition capture"));
	
	//Assuming a key with a multiline definition
	//dg_test = DataGenerator(TEST_RESOURCES_FILE_PATH + std::string("empty_file.txt"));
	

}
void get_random_entry_t() {
	DataGenerator dg_test = DataGenerator(TEST_RESOURCES_FILE_PATH + std::string("test_data.txt"));

	/*
	for (int i = 0; i < 20; i++) {
		std::pair<std::string, std::string> test1 = dg_test.get_random_entry();
		std::pair<std::string, std::string> test2 = dg_test.get_random_entry();

		if (test1.first != test2.first) {
			return 1;
		}
	}
	*/

	std::pair<std::string, std::string> test = dg_test.get_random_entry();

	static_assert(std::is_same<decltype(test.first), std::string>::value, "Return type is not std::string");
	static_assert(std::is_same<decltype(test.second), std::string>::value, "Return type is not std::string");

	//checking that limiting a length of the random word returns a word
	std::pair<std::string, std::string> test2 = dg_test.get_random_entry(5);
	assert(test2.first.length() == 5);

	std::pair<std::string, std::string> test4 = dg_test.get_random_entry(9);
	assert(test4.first.length() == 9);

}

int main() {

	make_wordmap_t();
	get_random_entry_t();

	return 0;
}