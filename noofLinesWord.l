%{
#include<stdio.h>
int lc=0, sc=0, wc=0, cc=0;
%}
%%
\n          { lc++; cc += yyleng; }
[ \t]       { sc++; cc += yyleng; }
[^\t\n ]+   { wc++; cc += yyleng; }
%%
int main(int argc, char* argv[])
{
    if(argc == 2)
    {
        yyin = fopen(argv[1], "r");
        if (yyin == NULL) {
            fprintf(stderr, "Error opening file: %s\n", argv[1]);
            return 1;
        }
    }
    else
    {
        printf("Enter the input: \n");
        yyin = stdin;
    }
    yylex();
    printf("The number of lines = %d\n", lc);
    printf("The number of spaces = %d\n", sc);
    printf("The number of words = %d\n", wc);
    printf("The number of characters = %d\n", cc);
    return 0;
}

int yywrap()
{
    return 1;
}
