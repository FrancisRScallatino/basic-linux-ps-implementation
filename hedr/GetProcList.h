/**
 * this module gets all processes owned by the user.
 */

#ifndef GETPROCLIST_H
#define GETPROCLIST_H

/** 
 * function to find processes
 * used a built in regex to search fo processes
 * then saves them in a matrix inside optProc
 */
void findProcesses(OptProc *optProc);

#endif