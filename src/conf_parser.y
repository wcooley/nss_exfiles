%{
#include <stdio.h>

#ifndef CONF_PATH
#define CONF_PATH ""
#endif /* CONF_PATH */

int _nss_exfiles_lex(void);
void _nss_exfiles_error (char const *);
%}

%union {
    char * string;
}

%debug
%token <string> PWBACKEND PATHNAME
%token NL
/* %type <string> statement */

%%

input:  /* empty */
     | input stmt
    ;

stmt: PWBACKEND ':' PATHNAME NL
        { printf("Backend: '%s', '%s'\n", $1, $3); }
    ;

%%

extern FILE *_nss_exfiles_in;
extern int _nss_exfiles_lineno;

void _nss_exfiles_error(const char *s) {
    fprintf(stderr, "Error: %s, line %d\n", s, _nss_exfiles_lineno);
}
