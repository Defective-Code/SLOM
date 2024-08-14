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

// Define a structure to hold key mappings
typedef struct {
    const char* keyName;
    WORD virtualKeyCode;
} KeyMapping;

void simulate_keypress(WORD key);

WORD get_virtual_keycode(const char* keyName);
