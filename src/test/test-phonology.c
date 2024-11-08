#include <stdio.h>
#include <olingc/phonology.h>

int test_blank_cell() {
	int fail_count = 0;
	phono_cell* blank_cell = init_blank_cell();
	
	if (!blank_cell->phonemes[0]) {
		printf("Phoneme was not created in blank cell!\n");
		fail_count += 1;
	} else {
		phoneme* p = blank_cell->phonemes[0];
		free_phono_cell(blank_cell);
		if (p != NULL) {
			printf("Phoneme was not properly freed from blank cell!\n");
			fail_count += 1;
		}
	}	

	return fail_count;
}

int test_blank_inits() {
	int fail_count = 0;
	printf("Testing blank structures...\n");
	
	fail_count += test_blank_cell();

	return fail_count;
}

int main(int argc, char* argv[]) {

	int fail_count = 0;
	fail_count += test_blank_inits();

	return fail_count;
}
