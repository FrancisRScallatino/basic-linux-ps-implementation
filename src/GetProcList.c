#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

#include "../hedr/OptProc.h"

void findProcesses(OptProc optProc){
    //char *thisUID = getuid();

    char *basePath = "/proc/";
    DIR *dirProc = opendir(basePath);
    struct dirent *dirProcEntry = readdir(dirProc);
    const char *regex = "^\\d+$";               //used to find dir entries starting and ending with numbers.
    int i = 0;

    int pathPIDLen = strlen(basePath) + optProc.maxPIDLen;
    uid_t thisUID = geteuid();

    while(dirProcEntry != NULL)
    {
        if(strcmp(regex, dirProcEntry -> d_name) > 0){
            if(i>1){ //skip first 2 entries ./ and ../
                //build the path to the processes who's name is d_name
                char *pathPID = malloc(pathPIDLen * sizeof(char));
                strcpy(pathPID, basePath);
                strcat(pathPID, dirProcEntry -> d_name);
                strcat(pathPID, "/stat");
                printf("\npath to pid: %s", pathPID);
                
                //get process directory variables
                struct stat *statbuf;
                stat(pathPID, statbuf);
                printf("\nUID = %d\nst_uid = %u\n", thisUID, statbuf -> st_uid);

                if(thisUID == statbuf -> st_uid){
                    strcpy(optProc.processes[i-2], dirProcEntry -> d_name);
                    printf("found process: %s\n", optProc.processes[i-2]);
                    free(pathPID);
                }
            }
            i++;
        }
        dirProcEntry = readdir(dirProc);
    }

    //printf("dirName: %s\n", dirProcentry.d_name);
}

void printProcessInfo(){
    printf("Printing processes!\n");
}