/**author: Francis R. Scallatino
 * 
 * This module will process the command line options,
 * setting state variables to record what the options specify.
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../hedr/OptProc.h"

OptProc Optproc_value (int argc, char **argv, int maxPIDLen, int maxPIDs)
{
    OptProc init = {argc, argv};

    init.maxPIDs = maxPIDs;
    init.maxPIDLen = maxPIDLen;

    //allocate char matrix to hold list of PIDs
    init.processes = malloc(sizeof(char*) * maxPIDs);
    for (int i=0; i < maxPIDs; i++) init.processes[i] = malloc(sizeof(char) * maxPIDLen);

    //allocate int array to keep track of user owned processes
    init.userOwned = malloc(sizeof(int) * maxPIDs);

    init.actualPIDs = 0;
    init.has_p = 0;
    init.has_s = 0;
    init.has_U = 0;
    init.has_S = 0;
    init.has_v = 0;
    init.has_c = 0;

    //search for and record what options are being used
    const char *options = "psUSvc";
    char opt;
    while((opt = getopt(argc, argv, options)) != -1){
        switch(opt){
            case 'p':
                init.has_p++;
                break;
            case 's':
                init.has_s++;
                break;
            case 'U':
                init.has_U++;
                break;
            case 'S':
                init.has_S++;
                break;
            case 'v':
                init.has_v++;
                break;
            case 'c':
                init.has_c++;
                break;
            default:
                printf("Please only use valid flags (i.e. %s)\n", options);
                exit(EXIT_FAILURE);
        }
    }
    return init;
}