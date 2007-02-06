#ifndef EXFILES_UTIL_H
#define EXFILES_UTIL_H

/* Utility functions */
int exfiles_open_file(char *, FILE **);

int exfiles_set_close_on_exec(FILE *);

void exfiles_trace_msg(char *);


#endif /* EXFILES_UTIL_H */
