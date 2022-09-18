#ifndef OPTPROC_H
#define OPTPROC_H

typedef struct OptProc {
    int argc;
    char **argv;
}OptProc;

/**
 * initialize option processing struct value
 */
OptProc Optproc_value (int argc, char **argv);

/**
 * print argument count and arguments from comand line
 */
void OptProc_Print(OptProc *self);

#endif