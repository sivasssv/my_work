#include "vector.h"
#include "stdlib.h"
#include <stdio.h>

void vector_init(Vector *v)
{
    v->capacity = 4;
    v->size = 0;
    v->data = malloc(v->capacity * sizeof(int));
}

void vector_resize(Vector *v, int newCapacity)
{
    int *newdata = malloc(newCapacity * sizeof(int));


    if(newdata == NULL)
    {
        printf("Memory allocation failed\n");
        exit(1);
    }

    for (int i = 0; i < v->size; i++)
    {   
        newdata[i] = v->data[i];
    }
    free(v->data);
    v->data = newdata; 
    v->capacity = newCapacity; 
}

void vector_push(Vector *v, int val)
{
    if(v->size == v->capacity)
    {
        vector_resize(v, v->capacity * 2);
    }
    v->data[v->size] = val;
    v->size++;
}

int vector_pop(Vector *v)
{
    if (v->size == 0)
    {
        printf("vector is empty\n");
        exit(1);
    }
    int popVal = v->data[v->size - 1];

    
    v->size--;

    return popVal;
}

void vector_insert(Vector *v, int index, int val)
{
    if(v->size == v->capacity)
    {
        vector_resize(v, v->capacity * 2);
    }

    if (v->size < index)
    {
        printf("INSERT: Index value is greater than size of vector\n");
    }
    else
    {
        for (int i = v->size + 1; i > index; i--)
        {
            v->data[i] = v->data[i - 1];
        }
        v->data[index] = val;
        v->size++;
    }
}

int vector_get(Vector *v, int index)
{
    if (v->size < index)
    {
        printf("GET: Index value is greater than size of vector\n");
        return -1;
    }
    else
    {
        return v->data[index];
    }
}

void vector_set(Vector *v, int index, int val)
{
    if (v->size < index)
    {
        printf("SET :Index value is greater than size of vector\n");
    }
    else
    {
        v->data[index] = val;
    }
    
}

int vector_size(Vector *v)
{
    return v->size;
}

int vector_capacity(Vector *v)
{
    return v->capacity;
}

void vector_print(Vector *v)
{
    for (int i = 0; i < v->size; i++)
    {
        printf("%d ", v->data[i]);
    }
    printf("\n");
}

void vector_free(Vector *v)
{
    free(v->data);
    v->capacity = 0;
    v->size = 0;
}
