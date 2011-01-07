%{
#include <stdio.h>
#include <string.h>
#include "conf_parser.h"
%}

%s BACKEND_S
%option yylineno
%option outfile="lex.yy.c"
%option noyywrap

path_re         \/[^;\n]+[^ ;\n]
fieldsep_re     [:]
backend_re      ^(passwd|group|shadow)

%%

<BACKEND_S>{path_re} {
        _nss_exfiles_lval.string = strdup(_nss_exfiles_text);
        return PATHNAME;
    }

<BACKEND_S>{fieldsep_re}  return _nss_exfiles_text[0];

<BACKEND_S>[ \t]   ; /* Ignore */

<BACKEND_S>\n  {
        BEGIN INITIAL;
        return NL;
    }

{backend_re} {
        _nss_exfiles_lval.string = strdup(_nss_exfiles_text);
        BEGIN BACKEND_S;
        return PWBACKEND;
    }

[ \t\n]  BEGIN INITIAL; /* Reset state and ignore */

#.*$    ; /* Specifically ignore comments, in case the catch-all changes */
.       ; /* Ignore all else */

%%

