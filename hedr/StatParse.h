/**
 * this program strictly parses /proc/[PID]/stat,
 * /proc/[PID]/statm and /proc/[PID]/cmdline
 * based on the given options
 */

//takes in process path and required file then opens and returns the 1-line string of information from that file
//fileName will be the stat, statm or cmdline files
FILE* getFileLineString(char *pPath, char *fileName);

//returns the number from the particular field based on the calling function
char* GetField(int n, char *x);

//returns utime from the stat file
char* GetUTime(char *pPath);

//returns the calling command from the cmdline file
char* GetCMDLine(char *pPath);

//returns state from the stat file
char* GetState(char *pPath);

//returns stime from the stat file
char* GetSTime(char *pPath);

//return size of virtual memory currently being used by this process
char* GetSize(char *pPath);