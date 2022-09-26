#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <regex.h>

#include "../hedr/OptProc.h"
#include "../hedr/StatParse.h"

void findProcesses(OptProc *optProc){
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
            optProc -> actualPIDs++;

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
            
            strcpy(optProc -> processes[i++], strtok(pathPID, "s"));
            if(thisUID == statbuf.st_uid){
                optProc -> userOwned[i-1]++;
                free(pathPID);
            }
        }
    }
    printf("\n");
}

/**
 * if has_p: display pid, utime, command that started the given process
 * if !has_p: display the above info for all USER OWNED processes
 * 
 * if has_s: display above info AND the single-character state (location: stat file, "state"(3) field)
 * 
 * if has_U: DO NOT display utime(14)
 * 
 * if has_S: display above info AND system time consumed (location: stat file, "stime"(15) field)
 * 
 * if has_v: display above info AND amount of virtual memory in use (location: statm file, "size"(1) field)
 * 
 * if has_c: DO NOT display command line that started this process
 */
void printProcessInfo(OptProc *optProc){
    printf("Printing processes!\n\n");
    char *strbuff = malloc(7*sizeof(char));
    
    //find proc info for 1 process
    if(optProc -> has_p){
        //search cmdline args for the PID
        for(int i = 0; i < optProc -> argc; i++){
            if(strcmp(optProc -> argv[i], "-p") == 0){
                int procFound = 0;
                //compare PID to all tracked processes
                char *pArg = malloc(sizeof(char) * (strlen(optProc -> argv[i+1])+3));   //used as substring for comparison
                strcpy(pArg, "/");
                strcat(pArg, optProc -> argv[i+1]);
                strcat(pArg, "/");
                //printf("optProc -> argv[%d] = %s\npArg = %s\n", i+1, optProc -> argv[i+1], pArg);
                
                for(int j = 0; j < optProc -> actualPIDs; j++){
                    //printf("\noptProc.processes[%d] = %s\noptProc.argv[%d] = %s\n",j, optProc -> processes[j], i+1, optProc -> argv[i+1]);
                    //if(optProc -> userOwned[j]) printf("USER OWNED\n");
                    if(strstr(optProc -> processes[j], pArg) != NULL){
                        //printf("FOUND PROCESS!\n");
                        procFound++;
                        break;
                    }
                }

                if(!procFound){
                    printf("process %s not found!\n", optProc -> argv[i+1]);
                    exit(EXIT_FAILURE);
                }
            }
        }
    }else{

    }
}