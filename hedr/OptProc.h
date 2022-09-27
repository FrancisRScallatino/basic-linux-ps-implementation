/**author: Francis R. Scallatino
 * 
 * this module helps with keeping track of which command line
 * arguments are being used.
 */

#ifndef OPTPROC_H
#define OPTPROC_H

typedef struct OptProc {
    int argc;           //number of arguments used in cammand line
    char **argv;        //the arguments used in the command line
    char **processes;   //matrix to keep track of list of processes in /proc/
    int *userOwned;     //tracked process at index i is user owned if !0
    int maxPIDs;        //size of space to allocate for processes taken from /proc/
    int actualPIDs;     //real count of the number of processes
    int maxPIDLen;      //size of space to allocate for the length of each PID taken from /proc/
    
    //used for tracking all options this program will support
    int has_p;
    int has_s;
    int has_U;
    int has_S;
    int has_v;
    int has_c;
}OptProc;

/**
 * initialize option processing struct OptProc
 * 
 * allocate char matrix for handling process paths
 * allocate int array to keep track of USER OWNED processes
 * record what options are used
 */
OptProc Optproc_value (int argc, char **argv, int maxPIDLen, int maxPIDs);

#endif