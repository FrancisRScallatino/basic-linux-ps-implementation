#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

#include "../hedr/OptProc.h"

void findProcesses(OptProc optProc){
    //char *thisUID = getuid();

    DIR *dirProc = opendir("/proc/");
    struct dirent *dirProcEntry = readdir(dirProc);
    const char *regex = "^\\d+";               //used to find dir entries starting and ending with numbers.
    int i = 0;

    while(dirProcEntry != NULL)
    {
        if(strcmp(regex, dirProcEntry -> d_name) > 0){
            if(i>1){
                strcpy(optProc.processes[i-2], dirProcEntry -> d_name);
                printf("found process: %s\n", optProc.processes[i-2]);
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