#include <stdio.h>
#include "input_handler_t.h"

int main() {

	printf("Running Tests");

	int check = 0;

	// Here we will call the other test methods/classes
	check+=capture_keypress_t();

	return check;
}