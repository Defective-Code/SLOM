// Simple assertion macro
#define ASSERT_EQ(expected, actual) \
    do { \
        if ((expected) != (actual)) { \
            std::cerr << "Assertion failed: (" << #expected << " == " << #actual << "), " \
                      << "function " << __FUNCTION__ << ", " \
                      << "file " << __FILE__ << ", " \
                      << "line " << __LINE__ << "." << std::endl; \
            return 1; \
        } \
    } while (false)

// char simulate_keypress(char* pressedKey);

// WORD get_virtual_keycode(const char* keyName); //for using windows library for getting keyboard inputs
