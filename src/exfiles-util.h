#ifndef EXFILES_UTIL_H
#define EXFILES_UTIL_H

/* Utility functions */
int exfiles_open_file(char *, FILE **);

int exfiles_set_close_on_exec(FILE *);

int exfiles_passwd_alloc_from_pw_entry(struct passwd *, char **);

int exfiles_copy_passwd_from_pw_entry(struct passwd *, char **);

void exfiles_passwd_destroy(struct passwd *);

int print_passwd_struct(FILE *, const struct passwd *);

int pretty_print_passwd_struct(FILE *, const struct passwd *);

int exfiles_passwd_cmp(const struct passwd *, const struct passwd *);

void exfiles_trace_msg(char *);

#endif /* EXFILES_UTIL_H */
