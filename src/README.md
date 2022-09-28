# project description

This project is a very basic implementation of a few functions similar to the ps command in Linux.

---

## implementation

---
after compiling this program with the Makefile, you can run ./MYps  to find a veriety of information.

### accepted flags

---

* -p \<PID\> will return the specified process, the amount of user time consumed by it and the command that called the process
  * if this option is excluded, it relays all above information for all *user owned* processes
* -s includes the single-character process state in the output
* -U excludes the user time consumed from the output
* -S includes the system time in the output
* -v includes the amount of virtual memory in the output
* -c exludes the calling command from the output

---

## Design

---
To keep everything neat, I put all my source files in 1 folder and header files in another folder. The modules come as follows

### MYps.c

#### *no header (main function location)*

---
This is where the code starts. this calls on 3 other source files to do the jobs described below. After they all complete, the rest of the code in this file prints out the information requested through the given flags.

### OptProc.c

---
This contains the typedefed struct OptProc used to contain and manage processes. This struct will keep track of commandline arguments, /proc/\[PID\] paths, as well as some extra bits of info used to make later code simpler.

### GetProcList.c

---
This module finds processes using a regex. If it finds a directory name with only numbers inside it will increment the number of processes it finds, record the path to this process directory, and update wether or not the current process is user owned.

### StatParse.c

---
This module implements file parsing. A few of the functions need to essentially achieve a very similar result so each function which returns the information it's called for (e.g. GetState() returns the process state) first sends it's process path to the GetFileLineString() function.

GetFileLineString() takes in the required file name (e.g. "stat" for the /proc/\[PID\]/stat file) and the path to the process directory. It concatinates the file name to the end of the path then pulls all information with getline() since it is only a 1 line file we'l ever be reading from.

This long string returns and in the case of 3 of the functions, they send this string alongside a fixed index to GetField(). This function returns the number at the field which the calling function needs.

for 2 of the functions I simply return the first token returned by strtok() because the very first piece of information is the one it needs.

finally, the GetCMDLine(). This one is unique because it sometimes returns an absolute path to the calling file. If it **does not** do this, GetCMDLine() simply returns the first token from strtok(). If it **does** do this, it finds the *last* token returned from strtok() and returns that instead.

### week 1

---

#### tasks at hand

* [x] Figure out how to get process file location
* [x] read from the entire file (must be able to extract all arguments)
* [x] Find the location of each file a particular flag wants you to find
  * [x] read it's contents (should be able to do this if second bullet is met, maybe?)

### week 3

---

### bugs

* was pulling wrong value from argv in GetProcList.c for comparisons to find if the user given process exists
  * fix: got some help from the TAs, found that getopt() pushes "non options" to the back of the argv matrix. since I use this earlier in the program I simply use the last index value to pull the user given PID
* not really a bug but there was an issue where some processes returned a full path name from the caller
  * used strtok() to "truncate" that path and pull the file name at the end of it.

#### notes

---

##### questions I had throughout this project period

1. Where is the Process UID and how to I compare to the current process UID?
   * located in the status file
   * can also use stat() for each individual process to get it's UID

1. What is meant by "display process information" for option -p
    * same default fields shown by the ps command