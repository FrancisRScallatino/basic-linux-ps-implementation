#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <regex.h>

#include "../hedr/OptProc.h"

void findProcesses(OptProc optProc){
    regex_t regex;
    unsigned int value = regcomp(&regex, "[0-9]",0);    //find only dirs with numbers (i.e. processes)
    char *basePath = "/proc/";
    DIR *dirProc = opendir(basePath);
    struct dirent *direntt;                             // readdir(dirProc);
    int i = 0;
    uid_t thisUID = getuid();

    while((direntt = readdir(dirProc)) != NULL)
    {
        value = regexec(&regex, direntt -> d_name, 0, NULL, 0);
                
        if( value  == 0)
        {
            //build the path to the processes who's name is d_name
            char *pathPID = (char*) malloc(32);
            strcpy(pathPID, basePath);
            strcat(pathPID, direntt -> d_name);
            strcat(pathPID, "/status");
            
            //get process directory variables
            struct stat statbuf;
            int success = stat(pathPID, &statbuf);
            if (success == -1){
                perror("stat:");
                continue;
            }

            if(thisUID == statbuf.st_uid){
                strcpy(optProc.processes[i++], strtok(pathPID, "s"));
                free(pathPID);
            }
        }
    }
}

void printProcessInfo(){
    printf("Printing processes!\n\n");
}