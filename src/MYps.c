/**Author: Francis R. Scallatino
 * 
 * This program is a basic version of the linux "ps" command
 */

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <ctype.h>

#include "../hedr/OptProc.h"
#include "../hedr/GetProcList.h"
#include "../hedr/StatParse.h"

void printProcessInfo(OptProc *optProc);

int main( int argc, char **argv)
{
    //get this process PID
    int maxNumOfProcesses = 30;
    int maxLenOfPID = 10;
    
    OptProc optProc = Optproc_value(argc, argv, maxLenOfPID, maxNumOfProcesses);

    findProcesses(&optProc);
    
    printProcessInfo(&optProc);

    free(optProc.processes);
}

/**
 * if has_p: display pid, utime(14), command that started the given process
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
 * if has_c: DO NOT display command that started this process
 */
void printProcessInfo(OptProc *optProc)
{
    //find proc info for 1 process
    if(optProc -> has_p)
    {
        //if given -p option without a PID to search for
        if(!isdigit((optProc -> argv[(optProc -> argc)-1][0]))){
            printf("No PID given with -p option!\n");
            exit(EXIT_FAILURE);
        }

        //using (optProc -> argc)-1 as index because of getopt() usage in OptProc.c
        //note: getopt() pushes "non options" to the back of argv
        char *pArg = malloc(sizeof(char) * (strlen(optProc -> argv[(optProc -> argc)-1])+3));   //used as substring for comparison
        strcpy(pArg, "/");
        strcat(pArg, optProc -> argv[(optProc -> argc)-1]);
        strcat(pArg, "/");

        //compare PID to all tracked processes
        int procFound = 0;
        for(int j = 0; j < optProc -> actualPIDs; j++){
            if(strstr(optProc -> processes[j], pArg) != NULL){
                strcpy(pArg, optProc -> processes[j]);
                procFound++;
                break;
            }
        }

        if(!procFound){
            printf("process %s not found!\n", optProc -> argv[(optProc -> argc)-1]);
            exit(EXIT_FAILURE);
        }

        //design columns
        printf("%-5s", "PID");
        if(!(optProc -> has_U)) printf("%10s", "utime");
        if(!(optProc -> has_c)) printf("%10s", "CMD");
        if(optProc -> has_s) printf("%10s", "state");
        if(optProc -> has_S) printf("%10s", "stime");
        if(optProc -> has_v) printf("%10s", "size");
        printf("\n");

        //print process info
        printf("%-5s", optProc -> argv[optProc -> argc - 1]);
        if(!(optProc -> has_U)) printf("%10s", GetUTime(pArg));
        if(!(optProc -> has_c)) printf("%10s", GetCMDLine(pArg));
        if(optProc -> has_s) printf("%10s", GetState(pArg));
        if(optProc -> has_S) printf("%10s", GetSTime(pArg));
        if(optProc -> has_v) printf("%10s", GetSize(pArg));
        printf("\n");
    }else{
        //design columns
        printf("%-5s", "PID");
        if(!(optProc -> has_U)) printf("%10s", "utime");
        if(!(optProc -> has_c)) printf("%10s", "CMD");
        if(optProc -> has_s) printf("%10s", "state");
        if(optProc -> has_S) printf("%10s", "stime");
        if(optProc -> has_v) printf("%10s", "size");
        printf("\n\n");

        //output info for all user owned processes
        for(int i=0; i<optProc -> actualPIDs; i++)
        {
            if(optProc -> userOwned[i]){
                //print process info
                printf("%-5s", GetPID(optProc -> processes[i]));
                if(!(optProc -> has_U)) printf("%10s", GetUTime(optProc -> processes[i]));
                if(!(optProc -> has_c)) printf("%10s", GetCMDLine(optProc -> processes[i]));
                if(optProc -> has_s) printf("%10s", GetState(optProc -> processes[i]));
                if(optProc -> has_S) printf("%10s", GetSTime(optProc -> processes[i]));
                if(optProc -> has_v) printf("%10s", GetSize(optProc -> processes[i]));
                printf("\n");
            }
        }
    }
}