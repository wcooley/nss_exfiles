#ifndef EXFILES_UTIL_H
#define EXFILES_UTIL_H

/* Utility functions */
struct passwd * exfiles_passwd_alloc_from_pw_entry(struct passwd *, char **);

struct passwd * exfiles_copy_passwd_from_pw_entry(struct passwd *, char **);

void exfiles_passwd_destroy(struct passwd *);

int print_passwd_struct(FILE *, const struct passwd *);

int pretty_print_passwd_struct(FILE *, const struct passwd *);

int exfiles_passwd_cmp(const struct passwd *, const struct passwd *);

#endif /* EXFILES_UTIL_H */
