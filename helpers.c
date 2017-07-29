
#include <stdlib.h>
#include <math.h>
#include "helpers.h"

double r2() {
    return (double)rand() / (double)RAND_MAX;
}

void intarray_init(IntArray *a, size_t initialSize) {
    a->array = (int *)malloc(initialSize * sizeof(int));
    a->used = 0;
    a->size = initialSize;
}

void intarray_insert(IntArray *a, int element) {
    if(a->used == a->size) {
        a->size = (a->size*3)/2+8;
        a->array = (int *)realloc(a->array, a->size * sizeof(int));
    }
    a->array[a->used++] = element;
}

void intarray_destroy(IntArray *a) {
    free(a->array);
    a->array = NULL;
    a->used = a->size = 0;
}