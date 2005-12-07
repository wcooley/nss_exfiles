%{
#include <stdio.h>

#ifndef CONF_PATH
#define CONF_PATH ""
#endif /* CONF_PATH */

int yylex(void);
void yyerror (char const *);
%}

%union {
    char * string;
}

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

extern FILE *yyin;
extern int yylineno;

int main(void) {
    yyin = fopen(CONF_PATH "exfiles.conf", "r");
    do {
        yyparse();
    } while(!feof(yyin));

    return 0;
}

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s, line %d\n", s, yylineno);
}
