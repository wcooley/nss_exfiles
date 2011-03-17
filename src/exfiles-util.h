#ifndef EXFILES_UTIL_H
#define EXFILES_UTIL_H

#include <stdio.h>

/* Utility functions */
int exfiles_open_file(const char *, FILE **);

int exfiles_set_close_on_exec(FILE *);

void exfiles_trace_msg(const char *);

char *qualify_file_path(const char *, char **);

/* Utility macros */
#define XSTR(s) STR(s)
#define STR(s) #s

#endif /* EXFILES_UTIL_H */
