#include <stdio.h>
#include <olingc/phonology.h>
#include <string.h>

void print_ok(char* function_name, int fail_count) {
	if (fail_count == 0) {
		printf("\033[32m%s OK.\033[0m\n", function_name);
	} else {
		printf("\033[5;37;41;1m%s failure.\033[0m\n", function_name);
	}
}

int test_blank_cell() {
	int fail_count = 0;
	phono_cell* blank_cell = init_blank_cell();
	
	if (!blank_cell->phonemes[0]) {
		fail_count += 1;
	}	
	if (blank_cell->phonemes[0]->parent != blank_cell) {
		fail_count += 1;
	}
	// Originally I wanted to make a test for this method, however it appears there's no real way
	// to verify that memory has indeed been freed without running into a segfault. I can get a segfault
	// from accessing data inside, so I believe it's working :)
	free_phono_cell(blank_cell);

	print_ok("Blank cell", fail_count);

	return fail_count;
}

int test_blank_row() {
	int fail_count = 0;
	phono_row* blank_row = init_blank_row();

	phono_cell* test_cell = init_blank_cell();

	if (!blank_row->cells[0]) {
		fail_count += 1;
	} else {
		phono_cell* extracted_cell = blank_row->cells[0];

		phoneme* test_phoneme = test_cell->phonemes[0];
		phoneme* extracted_phoneme = extracted_cell->phonemes[0];
	
		char* test_value = test_phoneme->value;
		char* extracted_value = extracted_phoneme->value;
	
		if (strcmp(extracted_value, test_value) != 0) {
			fail_count += 1;
		}
		if (blank_row->cells[0]->parent != blank_row) {
			fail_count += 1;
		}
	}
	
	print_ok("Blank row", fail_count);
	return fail_count;
}

int test_blank_inits() {
	int fail_count = 0;
	printf("Testing blank structures...\n");
	
	fail_count += test_blank_cell();
	fail_count += test_blank_row();

	return fail_count;
}

int main(int argc, char* argv[]) {

	int fail_count = 0;
	fail_count += test_blank_inits();
	
	if (fail_count == 0) {
		printf("Success!\n");
	} else {
		printf("Failures detected. Please see previous messages to see what failed.\n");
	}
	return fail_count;
}
