
#pragma execution_character_set( "utf-8" )

// Mapping of macronized characters to their normal equivalents
std::unordered_map<wchar_t, wchar_t> macron_map = {
    {L'ā', L'a'}, {L'ē', L'e'}, {L'ī', L'i'},
    {L'ō', L'o'}, {L'ū', L'u'}, {L'Ā', L'A'},
    {L'Ē', L'E'}, {L'Ī', L'I'}, {L'Ō', L'O'},
    {L'Ū', L'U'}
};

void clearScreen();
/**
    * @brief Splits a string into a vector of strings based on newline characters.
    *
    * @param input The input string to be split.
    * @return A vector of strings, each representing a line from the input.
*/
std::vector<std::string> splitStringOnNewline(const std::string& input);

//This method takes in a single character input by the user, and returns it in lowercase.
char getSingleCharacter();

//This method takes in a word input by the user, and returns it in lower cases removing any preceeding whitespace and/or newline characters
std::string getWord();

void clearLastNLines(int n);

std::wstring convertMacronsToNormal(const std::wstring& input);

std::wstring removeInvisibleCharacters(const std::wstring& input);

std::string removeWhitespace(const std::string& input);

std::string wstringToString(const std::wstring& wstr);

std::wstring stringToWstring(const std::string& str);