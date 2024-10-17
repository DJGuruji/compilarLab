%{
    int COMMENT = 0;
%}

identifier [a-zA-Z][a-zA-Z0-9]*

%%
"//".*                       { printf("single-line comment\n"); }
"/*"                         { COMMENT = 1; printf("multi-line comment start\n"); }
"*/"                         { COMMENT = 0; printf("multi-line comment end\n"); }
int |
float |
char                        { if (!COMMENT) printf("keyword: %s\n", yytext); }
"+"                         { if (!COMMENT) printf("plus operator\n"); }
"-"                         { if (!COMMENT) printf("minus operator\n"); }
{identifier}                { if (!COMMENT) printf("identifier: %s\n", yytext); }
[0-9]+                      { if (!COMMENT) printf("number: %s\n", yytext); }
[ \t\n]+                    { /* Ignore whitespace */ }
";"                         { if (!COMMENT) printf("semicolon\n"); }
.                           { if (!COMMENT) printf("unknown character: %s\n", yytext); }

%%

int main()
{
    FILE *file = fopen("input.c", "r");
    if (!file)
    {
        printf("Could not open the file input.c\n");
        return 1;
    }
    yyin = file;
    yylex();
    fclose(file);
    return 0;
}

int yywrap()
{
    return 1;
}
