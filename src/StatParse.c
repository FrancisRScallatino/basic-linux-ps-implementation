#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE* getFile(char *pPath, char *fileName)
{
    char *sPath = malloc(sizeof(char) * strlen(pPath) + 5);

    strcpy(sPath, pPath);
    strcat(sPath, fileName);

    //printf("stat path: %s\n", sPath);
    
    FILE *stat = fopen(sPath, "r");
    if(stat == NULL){
        char *errFrom;
        sprintf(errFrom, "%s path", fileName);
        perror(errFrom);
        exit(EXIT_FAILURE);
    }

    free(sPath);

    return stat;
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
    fclose(stat);
    
    char *null = NULL;
    char *token = strtok_r(x, " ", &null);
    //printf("\ntoken[0] = %s", token);

    //runs loop until it reaches the utime field (field #14)
    for(int i=0; i<13; i++){
        token = strtok_r(NULL, " ", &null);
        //printf("\ntoken[%d] = %s", i+1, token);
    }
    
    /*if((fgetsReturn = fgets(x, n, stat)) == NULL){
        perror("fgets");
        exit(EXIT_FAILURE);
    }*/

    //printf("\nValue at x[1] = %s\n", x);
    
    return token;
}