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
#include <dirent.h>
#include <sys/types.h>
#include <string.h>

int main( int argc, char **argv)
{
    int pid = getpid();
    char *pidString = sprintf(pidString, "%d", pid);
    char *cmdlnPath = "/proc/";
    cmdlnPath = strcat(cmdlnPath, pidString);
}