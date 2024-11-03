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


// IPA function
extern struct phono_system* generate_ipa();

// Initializing functions
extern struct phono_cell* init_blank_cell();
extern struct phono_row* init_blank_row();
extern struct phono_table* init_blank_table();
extern struct phono_system* init_blank_system();

// Freeing functions
extern void free_phoneme(struct phoneme* p);
extern void free_phono_cell(struct phono_cell* c);
extern void free_phono_row(struct phono_row* r);
extern void free_phono_table(struct phono_table* t);
extern void free_phono_system(struct phono_system* s);

#endif
