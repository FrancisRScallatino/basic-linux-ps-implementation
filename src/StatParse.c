#include <stdio.h>
#include <stdlib.h>

char* GetUTime(char *pPath)
{
    char *x = malloc(sizeof(char)*100);
    sprintf(x, "%s = %s", "UTIME", pPath);
    return x;
}