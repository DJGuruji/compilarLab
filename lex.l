%{
#include <stdio.h>
%}

%option noyywrap

%%

// Patterns for keywords, operators, numbers, identifiers, and unknown characters
"int"|"float"|"char"                { printf("Keyword: %s\n", yytext); }
"+"|"-"|"*"|"/"                     { printf("Operator: %s\n", yytext); }
[0-9]+                              { printf("Number: %s\n", yytext); }
[a-zA-Z_][a-zA-Z0-9_]*              { printf("Identifier: %s\n", yytext); }
\n                                  { /* Ignore new lines */ }
.                                   { printf("Unknown: %s\n", yytext); }

%%

int main() {
    while (yylex() != 0);  // Loop to continuously read input until EOF
    return 0;
}
