#ifndef _VECTOR_H
#define _VECTOR_H 

typedef struct
{
    int *data;
    int size;
    int capacity;
}Vector;

void vector_init(Vector *v);

void vector_push(Vector *v, int val);

int vector_pop(Vector *v);

void vector_resize(Vector *v, int newCapacity);

void vector_insert(Vector *v, int index, int val);

int vector_get(Vector *v, int index);

void vector_set(Vector *v, int index, int val);

int vector_size(Vector *v);

int vector_capacity(Vector *v);

void vector_print(Vector *v);

void vector_free(Vector *v);

#endif

