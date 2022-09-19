/** This module will process the command line options,
 * setting state variables to record what the options specify.
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../hedr/OptProc.h"

OptProc Optproc_value (int argc, char **argv)
{
    OptProc init = {argc, argv};
    init.has_p = 0;
    init.has_s = 0;
    init.has_U = 0;
    init.has_S = 0;
    init.has_v = 0;
    init.has_c = 0;

    const char *options = "psUSvc";
    char opt = getopt(argc, argv, options);
    while(opt != -1){
        switch(opt){
            case 'p':
                printf("has -p\n");
                init.has_p++;
                break;
            case 's':
                printf("has -s\n");
                init.has_s++;
                break;
            case 'U':
                printf("has -U\n");
                init.has_U++;
                break;
            case 'S':
                printf("has -S\n");
                init.has_S++;
                break;
            case 'v':
                printf("has -v\n");
                init.has_v++;
                break;
            case 'c':
                printf("has -c\n");
                init.has_c++;
                break;
            default:
                printf("Please only use valid flags (i.e. psUSvc)");
                exit(EXIT_FAILURE);
        }
        opt = getopt(argc, argv, options);
    }
    return init;
}

void OptProc_Print(OptProc *self)
{
    printf("# of arguments: %d\nArguments: ", self -> argc);

    for (int i=0; i<self -> argc; i++){
        printf("%s ", self -> argv[i]);
    }

    printf("\n");
}