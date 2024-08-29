#include "get_data.h"
#include <stdio.h>
#include <string>
#include <cassert>
#include <type_traits>

int make_wordmap_t() {
	//Testing if key contains multiple space seperated words
	std::string filepath = TEST_RESOURCES_FILE_PATH + std::string("test_data.txt");
	std::cout << filepath << std::endl;
	DataGenerator dg_test = DataGenerator(filepath);

	assert(dg.wordmap["hello"] == "a standard greeting in the English language");
	assert(dg.wordmap["world"] == "meaning either the earth, together with all of its countries and peoples or a particular region or group of countries");
	assert(dg.wordmap.size() == 2);

	assert(dg.wordmap.find("keyWithNoDefinition") == dg.wordmap.end());
	
	//Assuming a key with a multiline definition
	dg_test = DataGenerator(TEST_RESOURCES_FILE_PATH + std::string("empty_file.txt"));
	assert(dg.wordmap["keyWithMultilineDef"] == "This is a multiline definition.");

	return 0;
}
int get_random_entry_t() {
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
	std::pair<std::string, std::string> test2 = dg_test.get_random_entry(2);
	if (test2.first.length() != 2) return 1;

	std::pair<std::string, std::string> test3 = dg_test.get_random_entry(3);
	if (test3.first.length() != 3) return 1;

	std::pair<std::string, std::string> test4 = dg_test.get_random_entry(4);
	if (test4.first.length() != 4) return 1;
	
	std::pair<std::string, std::string> test8 = dg_test.get_random_entry(8);
	if (test8.first.length() != 8) return 1;

	return 0;
}

int main() {
	int test_results = 0;
	test_results += make_wordmap_t();
	test_results += get_random_entry_t();

	return test_results;
}