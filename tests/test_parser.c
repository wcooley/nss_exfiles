#include <stdio.h>

/* Quick & dirty manual test of parser for now */

extern FILE *_nss_exfiles_in;
extern int _nss_exfiles_lineno, _nss_exfiles_debug;

int main(int argc, const char* argv[]) {
    _nss_exfiles_in = fopen(argv[1], "r");
    _nss_exfiles_debug=1;
    do {
        _nss_exfiles_parse();
    } while (!feof(_nss_exfiles_in));

    return 0;
}
