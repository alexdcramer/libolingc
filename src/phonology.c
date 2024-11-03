#include <stdlib.h>
#include "phonology.h"

phono_cell* init_blank_cell() {
	phoneme* p = malloc(sizeof(phoneme));
	p->value = malloc(sizeof(char));
	p->def = malloc(sizeof(char));

	phono_cell* c = malloc(sizeof(phono_cell));
	c->phonemes = &p;
	c->def = malloc(sizeof(char));
	
	p->cell_def = c->def;

	return c;
}
