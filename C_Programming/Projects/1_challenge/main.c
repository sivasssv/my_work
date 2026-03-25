#include <stdio.h>
//#include <stddef.h>
#include "string1.h"
int main()
{
    printf("strlen: %zu\n", strlen("hello"));

    char a[10];
    printf("copied string : %s\n", strcpy(a, "hi"));
 
    char *p = strstr("hello world", "world");
    if( p != NULL)
    {
        printf("substring: %s\n", p);
    }

    /*String compare */
    printf("comparision : %d\n", strcmp("abc", "abc"));
    printf("comparision: %d\n", strcmp("abc", "abd"));
#if 1
    char s[] = "a, b, c, d";
    char *token = strtok(s, ",");
    
    while(token != NULL)
    {
        printf("token: %s\n", token);
        token = strtok(NULL, ",");
    }
#endif
    return 0;
}


