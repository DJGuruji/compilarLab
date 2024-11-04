%{
#include <stdio.h>
int v = 0; // Vowel count
int c = 0; // Consonant count
%}
%%
[aeiouAEIOU]       { v++; }
[b-df-hj-np-tv-zB-DF-HJ-NP-TV-Z] { c++; }
\n                 {
                    printf("Number of vowels are: %d\n", v);
                    printf("Number of consonants are: %d\n", c);
                    v = 0;
                    c = 0;
                  }
.                  { /* ignore any other characters */ }
%%
int main()
{
    printf("Enter the string of vowels and consonants:\n");
    yylex();
    return 0;
}

int yywrap()
{
    return 1;
}
