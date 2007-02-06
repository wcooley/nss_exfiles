/* Group utility functions */

#ifndef EXFILES_UTIL_GRP_H
#define EXFILES_UTIL_GRP_H

int exfiles_group_alloc_from_gr_entry(struct group *, char **);

int exfiles_copy_group_from_gr_entry(struct group *, char **);

void exfiles_group_destroy(struct group *);

#endif /* EXFILES_UTIL_GRP_H */
