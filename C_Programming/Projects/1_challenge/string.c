#include "string1.h"

static int is_delim(const char* delim, char ptr)
{
    while (*delim)
    {
        if(ptr == *delim)
        {
            return 1;
        }
        delim++;
    }
    return 0;
}

size_t strlen(const char *str)
{
    size_t count = 0;
    while(str[count] != '\0')
    {
        count++;
    }
    return count;
}

char *strcpy(char *dest, const char *src)
{
#if 0
    int count = 0;
    while (src[count] != '\0')
    {
        dest[count] = src[count];
        count++;
    }
    dest[count] = '\0';

    return dest;
#else 
    char *start = dest;

    while((*dest++ = *src++));
    return start;

#endif
}

char *strstr(const char *haystack, const char *needle)
{
    if (*needle == '\0')
    {
        return (char*)haystack;
    }
    const char *sub = needle;
    const char *main = haystack;

    while (*haystack != '\0' )
    {
        sub = needle;
        main = haystack;
        while (*haystack == *sub && *haystack && *sub)
        {
            haystack++;
            sub++;
        }
            if (*sub == '\0')
            {
                return (char*)main;
            }
        
        haystack++;
    }
    return NULL;
}

int strcmp(const char *s1, const char *s2)
{
    while (*s1 && *s1 == *s2)
    {
        s1++;
        s2++;
    }

    return (unsigned char)*s1 - (unsigned char)*s2;
}
#if 1
char *strtok(char *str, const char *delim)
{
    static char *ptr;
    char *start;
    if (str)
    {
        ptr = str;
    }

     if (!ptr)
    {
        return NULL;
    }

    while (*ptr && is_delim(delim, *ptr))
    {
        ptr++;
    }

    if(*ptr == '\0')
    {
        return NULL;
    }

    start = ptr;
    while (*ptr && !is_delim(delim, *ptr))
    {
        ptr++;
    }
    
    if(*ptr != '\0')
    {
        *ptr = '\0';
        ptr++;
       
    }
    return start;
}



#endif