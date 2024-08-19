#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

class DataGenerator{

public:
    std::unordered_map<std::string,std::string> wordmap;

    DataGenerator() {
        make_wordmap();
    }

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
        bool nextkey {true};
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
};

