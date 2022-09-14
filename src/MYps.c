/** reference comment, will be deleted later as it is unecessary and legnthy
 * 
 * 
 * I took 'parsing the command line' to mean parsing the cmdline file. However,
 * it could also mean parsing the user's command line input. Achieving either would
 * be reasonable for the first deliverable.
 *  
 * You should also have a general function that extracts the whole contents of the
 * various files we care about. It should be clear that it reads the whole file.
 * Sane functions like read() or fread() can achieve this. The function should at a
 * minimum take an argument for the pid (the type is up to you) as you'll be to
 * build a string to lead to the correct proc files for a specific program.
 * 
 * To further clarify, the notes I gave in response to PlusA are with an eye toward
 * the challenges of parsing the cmdline file
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>

int main( int argc, char **argv)
{
    //get this process PID
    int pid = getpid();
    char *pidString = malloc(5*sizeof(char));
    sprintf(pidString, "%d", pid);

    //create path to this process cmdline file
    char *cmdlnPath = malloc(50*sizeof(char));
    cmdlnPath = strcat(cmdlnPath, "/proc/");
    cmdlnPath = strcat(cmdlnPath, pidString);
    cmdlnPath = strcat(cmdlnPath, "/cmdline");

    printf("Full cmdline path: %s\n\n", cmdlnPath);

    FILE *thisCmdlineFile = fopen(cmdlnPath, "r");

    char *line = malloc(128*sizeof(char));
    size_t len = 0;
    ssize_t read;
    while((read = getline(&line, &len, thisCmdlineFile)) != -1)
    {
        printf("%s\n", line);
    }
    /*int i = 1; //number of cammand line args
    while((ent = ))
    {
        printf("entry %d: %s\n", i, ent);
    }*/
}