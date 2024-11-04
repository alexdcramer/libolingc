#ifndef _LIBOLINGC_PHONOLOGY_H_
#define _LIBOLINGC_PHONOLOGY_H_

/**
 * The following typedefs are for components of a phono_system
 *
 * A phono_system can be thought of as simply a list of 3D tables, combined with metadata
 * 
 * Each phono_system is made of 1 or more instances of phono_table
 * 
 * A phono_table is a three-dimentional table containing 1 or more instances of phono_row, alongside some information about the sounds it contains
 * 
 * These can be thought of as the consonant and vowel tables of the IPA. Non-pulmonics can also be stored in a table, but there isn't any columnar data
 * needed for those.
 * 
 * Each table contains n amount of phono_rows. These can be thought of as rows in the IPA consonant table (plosives, nasals, etc.)
 * phono_rows have their size defined by their parent, as all rows need to be the same size. This does cause some data to be used for empty cells,
 * but it should be fine.
 *
 * Each row contains n amount of phono_cells. These can be thought of as the unvoiced/voiced pairs in the IPA.
 *
 * Each cell contains n amount of phonemes. These can be thought of as the individual characters of the IPA.
 *
 * Preferably, def strings should point back to the strings defined by the table
 *
 */
typedef struct phoneme {
	char* value;
	char* def; // for IPA: voiced/unvoiced
	struct phono_cell* parent;
}phoneme;

typedef struct phono_cell {
	char* def; // for IPA: bilabial/labiodental/.../glottal
	phoneme** phonemes;
	struct phono_row* parent;
}phono_cell;

typedef struct phono_row {
	char* def; // for IPA: plosive/nasal/.../lateral approximant
	phono_cell** cells;

	struct phono_table* parent;
}phono_row;

typedef struct phono_table {
	phono_row** rows;
	int *row_size, *num_rows, *cell_size;
	char **row_defs, **column_defs, **cell_defs;
	struct phono_system* parent;
}phono_table;

typedef struct phono_system {
	phono_table** tables;
	char** diacritics;
	int *num_tables, *num_diacritics;
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
