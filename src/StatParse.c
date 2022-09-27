#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* getFileLineString(char *pPath, char *fileName)
{
    char *fPath = malloc(sizeof(char) * strlen(pPath) + 5); //used to get specific file path for given process
    char *x = NULL;                                         //string of information from required file
    size_t n = 0;                                           //buffer size for getline()

    //build path to needed file without changing original pPath
    strcpy(fPath, pPath);
    strcat(fPath, fileName);

    //printf("stat path: %s\n", fPath);
    FILE *stat = fopen(fPath, "r");
    if(stat == NULL){
        char *errFrom;
        sprintf(errFrom, "%s path", fileName);
        perror(errFrom);
        exit(EXIT_FAILURE);
    }
    free(fPath);
    
    if(getline(&x, &n, stat) == -1){
        perror("getline");
        exit(EXIT_FAILURE);
    }
    fclose(stat);

    return x;
}

char* GetUTime(char *pPath)
{

    char *x = getFileLineString(pPath, "stat");
    
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

char* getCMDLine(char *pPath)
{
    char *x = getFileLineString(pPath, "cmdline");

    return strtok(x, " ");
}

char* getState(char *pPath)
{
    char *x = getFileLineString(pPath, "stat");
    
    char *null = NULL;
    char *token = strtok_r(x, " ", &null);
    //printf("\ntoken[0] = %s", token);

    //runs loop until it reaches the utime field (field #14)
    for(int i=0; i<2; i++){
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