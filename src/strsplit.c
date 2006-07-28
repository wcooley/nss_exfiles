
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * strcnt - Count the number of occurrances of a character in a string
 */
int strcnt(const char * str, const char char_to_cnt) {
    int count = 0;

    /* Abort early if the str is bogus */
    if (NULL == str)
        return 0;

    while ('\0' != *str) {
        if (*str == char_to_cnt)
            ++count;
        ++str;
    }

    return count ;
}

/*
 * strsplit - Split a string up into an array of strings, given a character
 * to use as delimiter.
 */
char ** strsplit(const char * splitstr, const char splitchar) {
    int splitcnt = 0;
    int i, j, slen;
    char **splitdst;
    const char *begin = splitstr;
    const char *end = splitstr;
    splitcnt = strcnt(splitstr, splitchar);

    /* splitcnt+2 == number of items plus terminating NULL */
    splitdst = malloc((size_t) sizeof(char *) * (splitcnt + 2));
    if (NULL == splitdst) return NULL;

    splitdst[splitcnt+1] = NULL;

    for (i=0; i <= splitcnt; ++i) {

        while (*end != splitchar && '\0' != *end) ++end;

        slen = end - begin;
        splitdst[i] = malloc((size_t)slen+1);
        /* FIXME - Need to think about this */
        if (NULL == splitdst[i])
            return splitdst;
        splitdst[i][slen] = '\0';
        strncpy(splitdst[i], begin, (size_t)slen);
        ++end;
        begin = end;
    }

    return splitdst;
}

void strsplit_free(char ** splat) {
    char ** splatorig = splat;
    while (NULL != *splat) {
        free(*splat);
        ++splat;
    }
    free(splatorig);
}
