
#ifndef HELPERS_H_
#define HELPERS_H_


typedef struct IntArray{
    int *array;
    size_t used;
    size_t size;
} IntArray;


double r2();
void intarray_init(IntArray *a, size_t initialSize);
void intarray_insert(IntArray *a, int element);
void intarray_destroy(IntArray *a);

#endif /* HELPERS_H_ */