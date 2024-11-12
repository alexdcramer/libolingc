#include <stdlib.h>
#include <strings.h>
#include "phonology.h"

/**
 * =================================
 * | Blank Datatype Initialization |
 * =================================
 */

phono_cell* init_blank_cell() {
	phono_cell *c = malloc(sizeof(phono_cell));
	
	c->phonemes = malloc(sizeof(phoneme*));
	c->phonemes[0] = malloc(sizeof(phoneme));
	c->phonemes[0]->value = malloc(sizeof(char));
	*c->phonemes[0]->value = ' ';
	c->phonemes[0]->parent = c;


	return c;
}

phono_row* init_blank_row() {
	
	phono_row *r = malloc(sizeof(phono_row));

	r->cells = malloc(sizeof(phono_cell*));
	r->cells[0] = init_blank_cell();
	r->cells[0]->parent = r;

	r->def = malloc(sizeof(char));
	
	return r;
}

phono_table* init_blank_table() {

	phono_table* t = malloc(sizeof(phono_table));

	phono_row* r = init_blank_row();
	r->parent = t;

	t->rows = &r;
	int* rowsize = malloc(sizeof(int));
	int* numrows = malloc(sizeof(int));
	int* cellsize = malloc(sizeof(int));
	*rowsize = 1;
	*numrows = 1;
	*cellsize = 1;
	t->row_size = rowsize;
	t->num_rows = numrows;
	t->cell_size = cellsize;

	char* rowdef = malloc(sizeof(char));
	char* columndef = malloc(sizeof(char));
	char* celldef = malloc(sizeof(char));
	t->row_defs = &rowdef;
	t->column_defs = &columndef;
	t->cell_defs = &celldef;

	// set blank children defs to properly point to table defs
	free(r->def);
	r->def = rowdef;

	phono_cell* c = r->cells[0];
	free(c->def);
	c->def = columndef;

	phoneme* p = c->phonemes[0];
	free(p->def);
	p->def = celldef;

	return t;
}

phono_system* init_blank_system() {

	phono_system* s = malloc(sizeof(phono_system));
	char* diacritics = malloc(sizeof(char));
	s->diacritics = &diacritics;
	
	int* numtables = malloc(sizeof(int));
	*numtables = 1;
	s->num_tables = numtables;
	
	phono_table* t = init_blank_table();
	s->tables = &t;
	
	return s;
}

/**
 * =====================
 * | Freeing Functions |
 * =====================
 */

void free_phoneme(phoneme* p) {
	if (p != NULL) {
		free(p->value);
	}
	free(p);
}

void free_phono_cell(phono_cell* c) {
	if (c != NULL) {
		if (c->parent != NULL) {
			if (c->parent->parent != NULL) {
				for (int i = 0; i < *(c->parent->parent->cell_size); i++) {
					free_phoneme(c->phonemes[i]);
				}
			}
		}
	
		// If size isn't defined by the parent (ex. no parent), at least free the phoneme at index 0
		if (c->phonemes != NULL) {
			free_phoneme(c->phonemes[0]);
		}	
	
		free(c->phonemes);
	}
	free(c);
}

void free_phono_row(phono_row* r) {
	for (int i = 0; i < *(r->parent->row_size); i++) {
		free_phono_cell(r->cells[i]);
	}
	free(r->cells);
	free(r);
}

void free_phono_table(phono_table* t) {
	
	
	for (int i = 0; i < *(t->row_size); i++) {
		free(t->column_defs[i]);
	}
	free(t->row_size);

	for (int i = 0; i < *(t->num_rows); i++) {
		free(t->row_defs[i]);
	}


	for (int i = 0; i < *(t->cell_size); i++) {
		free(t->cell_defs[i]);
	}
	
	for (int i = 0; i < *(t->num_rows); i++) {
		free_phono_row(t->rows[i]);
	}

	free(t->num_rows);
	free(t->row_defs);
	free(t->column_defs);
	free(t->cell_defs);

	free(t);
}

void free_phono_system(phono_system* s) {
	for (int i = 0; i < *(s->num_tables); i++) {
		free_phono_table(s->tables[i]);
	}

	for (int i = 0; i < *(s->num_diacritics); i++) {
		free(s->diacritics[i]);
	}

	free(s->num_tables);
	free(s->num_diacritics);

	free(s);
}
