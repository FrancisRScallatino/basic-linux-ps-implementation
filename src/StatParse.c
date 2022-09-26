#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE* getFile(char *pPath, char *fileName)
{
    char *sPath = malloc(sizeof(char) * strlen(pPath) + 5);

    strcpy(sPath, pPath);
    strcat(sPath, fileName);

    printf("stat path: %s\n", sPath);
    
    FILE *stat = fopen(sPath, "r");
    if(stat == NULL){
        char *errFrom;
        sprintf(errFrom, "%s path", fileName);
        perror(errFrom);
        exit(EXIT_FAILURE);
    }
}

char* GetUTime(char *pPath)
{
    char *x = NULL;
    size_t n = 0;

    FILE* stat = getFile(pPath, "stat");
    
    if(getline(&x, &n, stat) == -1){
        perror("getline");
        exit(EXIT_FAILURE);
    }
    
    /*if((fgetsReturn = fgets(x, n, stat)) == NULL){
        perror("fgets");
        exit(EXIT_FAILURE);
    }*/

    printf("\nValue at x[1] = %s\n", x);
    
    return x;
}