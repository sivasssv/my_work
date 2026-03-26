#include <stdio.h>
#include "vector.h"

int main()
{
    Vector v;

    vector_init(&v);
    
    printf("\n====== PUSH TEST =======\n");
    for (int i = 1; i <= 10; i++)
    {       
        vector_push(&v, i * 10);    
    }
    vector_print(&v);
    printf("Size: %d\n", vector_size(&v));
    printf("Capacity: %d\n", vector_capacity(&v));
#if 1
    printf("\n====== INSERT TEST =======\n");    
    vector_insert(&v, 2, 999);
    vector_insert(&v, 0, 111);
    vector_print(&v);
    printf("Size: %d\n", vector_size(&v));
    printf("Capacity: %d\n", vector_capacity(&v));

    printf("\n====== POP TEST =======\n");
    printf("Popped: %d\n", vector_pop(&v));  
    printf("Popped: %d\n", vector_pop(&v));  
    vector_print(&v);
    printf("Size: %d\n", vector_size(&v));
    printf("Capacity: %d\n", vector_capacity(&v));


    printf("\n======  GET / SET TEST =======\n");  
    printf("Value at index 3: %d\n", vector_get(&v, 3));
    vector_set(&v, 3, 555); 
    vector_print(&v); 
    printf("Size: %d\n", vector_size(&v));
    printf("Capacity: %d\n", vector_capacity(&v));

    printf("\n====== SIZE / CAPACITY TEST =======\n"); 
    printf("Size: %d\n", vector_size(&v));
    printf("Capacity: %d\n", vector_capacity(&v)); 

    vector_free(&v);
#endif
    return 0;
}


