
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * strcnt - Count the number of occurrances of a character in a string
 */
int strcnt(const char * str, const char charcnt) {
    int cnt = 0;

    while('\0' != *str) {
        if (*str == charcnt)
            ++cnt;
        ++str;
    }

    return cnt ;
}

/*
 * strsplit - Split a string up into an array of strings, given a character
 * to use as delimiter.
 */
char ** strsplit(const char * splitstr, const char splitchar) {
    int splitcnt = 0;
    int i, j, slen;
    char **splitdst;
    char *begin, *end;

    splitcnt = strcnt(splitstr, splitchar);

    /* splitcnt+2 == number of items plus terminating NULL */
    splitdst = malloc((size_t) sizeof(char *) * (splitcnt + 2));
    if (NULL == splitdst) return NULL;

    splitdst[splitcnt+1] = NULL;

    end = begin = splitstr;

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
