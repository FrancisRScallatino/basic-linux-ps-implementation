/**
 * this program strictly parses /proc/[PID]/stat,
 * /proc/[PID]/statm and /proc/[PID]/cmdline
 * based on the given options
 */

//takes in process path and required file then opens and returns the filestream for that file
//fileName will be the stat, statm or cmdline files
FILE* getFile(char *pPath, char *fileName);

//returns utime from the stat file
char* GetUTime();