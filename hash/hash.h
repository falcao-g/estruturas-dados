#ifndef __HASH__
#define __HASH__
#include <stdint.h>

typedef struct {
	uintptr_t * table;
	int size;
	int max;
	uintptr_t deleted;
	char* (*get_key)(void *);
} thash;

int hash_constroi(thash* h, int max, char* (*get_key)(void*));
#endif
