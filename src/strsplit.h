
#ifndef STRSPLIT_H
#define STRSPLIT_H

int strcnt(const char *, const char);

char **strsplit (const char *, const char);

void strsplit_free(char **);

#endif /* STRSPLIT_H */
