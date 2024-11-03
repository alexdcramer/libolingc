#ifndef _LIBOLINGC_PHONOLOGY_H_
#define _LIBOLINGC_PHONOLOGY_H_

typedef struct phoneme {
	char* value, def, cell_def, row_def, table_def;
}phoneme;

typedef struct phono_cell {
	struct phoneme** phonemes;
	char* def, row_def, table_def;
}phono_cell;

typedef struct phono_row {
	struct phono_cell** cells;
	int* cell_size;
	char* def, table_def;
}phono_row;

typedef struct phono_table {
	struct phono_row** rows;
	int* row_size, num_rows;
	char* def;
}phono_table;

typedef struct phono_system {
	struct phono_table** tables;
	char** diacritics;
	int num_tables;
}phono_system;


// Create a phono_system with the same structure as the IPA
extern struct phono_system* generate_ipa();

/**
 * ==========================
 * | Initializing Functions |
 * ==========================
 **/

// Create a blank phono_cell containing one blank phoneme
extern struct phono_cell* init_blank_cell();

// Create a blank phono_row containing one blank cell
extern struct phono_row* init_blank_row();

// Create a blank phono_table containing one blank row
extern struct phono_table* init_blank_table();

// Create a blank phono_system containing one blank table
extern struct phono_system* init_blank_system();

/**
 * =====================
 * | Freeing Functions |
 * =====================
 **/

// The following functions are required for use as to prevent memory leaks. free() likely will not work on these objects.

// Free a phoneme from memory.
extern void free_phoneme(struct phoneme* p);
// Free a phono_cell from memory.
extern void free_phono_cell(struct phono_cell* c);
// Free a phono_row from memory.
extern void free_phono_row(struct phono_row* r);
// Free a phono_table from memory.
extern void free_phono_table(struct phono_table* t);
// Free a phono_system from memory.
extern void free_phono_system(struct phono_system* s);

#endif
