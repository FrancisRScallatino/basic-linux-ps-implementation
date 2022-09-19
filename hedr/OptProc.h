#ifndef OPTPROC_H
#define OPTPROC_H

typedef struct OptProc {
    int argc;
    char **argv;
    int num_of_options;
    int has_p;
    int has_s;
    int has_U;
    int has_S;
    int has_v;
    int has_c;
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