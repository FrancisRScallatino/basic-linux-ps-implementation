#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* GetFileLineString(char *pPath, char *fileName)
{
    char *fPath = malloc(sizeof(char) * strlen(pPath) + 5); //used to get specific file path for given process
    char *x = NULL;                                         //string of information from required file
    size_t n = 0;                                           //buffer size for getline()

    //build path to needed file without changing original pPath
    strcpy(fPath, pPath);
    strcat(fPath, fileName);
    
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

char* GetField(int n, char *x)
{
    char *null = NULL;
    char *token = strtok_r(x, " ", &null);

    //runs loop until it reaches the utime field (field #14)
    for(int i=0; i<n; i++){
        token = strtok_r(NULL, " ", &null);
    }

    return token;
}

char* GetPID(char* pPath)
{
    char *x = GetFileLineString(pPath, "stat");

    return strtok(x, " ");
}

char* GetUTime(char *pPath)
{
    char *x = GetFileLineString(pPath, "stat");
    
    return GetField(13, x);
}

char* GetCMDLine(char *pPath)
{
    char *x = GetFileLineString(pPath, "cmdline");
    char *cmd = strtok(x, " ");
    
    FILE *isFile = fopen(cmd, "r");

    if(!isFile){
        return cmd;
    }else{
        //if it is a file path, get the file name at the end of the path
        fclose(isFile);
        char *saveptr = NULL;
        char *prevToken = malloc(sizeof(char)*64);
        char *token = strtok_r(cmd, "/", &saveptr);
        while(token != NULL){
            strcpy(prevToken, token);
            token = strtok_r(NULL, "/", &saveptr);
        }
        return prevToken;
    }
}

char* GetState(char *pPath)
{
    char *x = GetFileLineString(pPath, "stat");
    
    return GetField(2, x);
}

char* GetSTime(char *pPath)
{
    char *x = GetFileLineString(pPath, "stat");
    
    return GetField(14, x);
}

char* GetSize(char *pPath)
{
    char *x = GetFileLineString(pPath, "statm");

    return strtok(x, " ");
}