%{
#include <stdio.h>
#include <stdlib.h>
int flag = 0;
int yylex(void);  // Declare yylex
void yyerror(const char *s);  // Declare yyerror
%}

%token NUMBER
%left '+' '-'
%left '*' '/' '%'
%left '(' ')'

%%
ArithmeticExpression:
    E { printf("\nResult = %d\n", $1); return 0; }
;

E:
    E '+' E { $$ = $1 + $3; }
  | E '-' E { $$ = $1 - $3; }
  | E '*' E { $$ = $1 * $3; }
  | E '/' E { 
        if ($3 == 0) {
            printf("Error: Division by zero\n");
            flag = 1;
            YYABORT;
        } else {
            $$ = $1 / $3;
        }
    }
  | E '%' E { 
        if ($3 == 0) {
            printf("Error: Modulo by zero\n");
            flag = 1;
            YYABORT;
        } else {
            $$ = $1 % $3;
        }
    }
  | '(' E ')' { $$ = $2; }
  | NUMBER    { $$ = $1; }
;

%%
int main() {
    printf("\nEnter Any Arithmetic Expression:\n");
    yyparse();
    if (flag == 0)
        printf("\n\n");
    return 0;
}

void yyerror(const char *s) {
    printf("\nInvalid expression: %s\n\n", s);
    flag = 1;
}
