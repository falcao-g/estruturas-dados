#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "hash.h"

int hash_constroi(thash* h, int max, char* (*get_key)(void*)) {
	h->table = calloc(sizeof(void*), max);
	if (h->table == NULL) {
		return EXIT_FAILURE;
	}
	h->size = 0;
	h->max = max;
	h->deleted = (uintptr_t)&(h->size);
	h->get_key = get_key;
	return EXIT_SUCCESS;
}
