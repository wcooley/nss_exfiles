%{
#include <stdio.h>
#include <string.h>
#include "exfiles_conf.tab.h"
%}

%s BACKEND_S
%option yylineno

path_re         \/[^;\n]+[^ ;\n]
fieldsep_re     [:]
backend_re      ^(passwd|group|shadow)

%%

<BACKEND_S>{path_re} { 
        yylval.string = strdup(yytext); 
        return PATHNAME;
    }

<BACKEND_S>{fieldsep_re}  return yytext[0];

<BACKEND_S>[ \t]   ; /* Ignore */

<BACKEND_S>\n  { 
        BEGIN INITIAL;
        return NL; 
    }

{backend_re} {
        yylval.string = strdup(yytext); 
        BEGIN BACKEND_S; 
        return PWBACKEND; 
    }

[ \t\n]  BEGIN INITIAL; /* Reset state and ignore */

#.*$    ; /* Specifically ignore comments, in case the catch-all changes */
.       ; /* Ignore all else */ 

%%

