/** This module will process the command line options,
 * setting state variables to record what the options specify.
 */
#include <stdio.h>

#include "../hedr/OptProc.h"

OptProc Optproc_value (int argc, char **argv)
{
    OptProc init = {argc, argv};
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