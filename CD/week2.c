
%{
#include <stdio.h>
%}

%%
/* Keywords */
int|float|char|double|if|else|while|for|return|void
{
    printf("Keyword: %s\n", yytext);
}

/* Identifiers */
[a-zA-Z_][a-zA-Z_0-9]*
{
    printf("Identifier: %s\n", yytext);
}

/* Numbers */
[0-9]+
{
    printf("Number: %s\n", yytext);
}

/* Operators */
"+"|"-"|"*"|"/"|"="|"<"|">"
{
    printf("Operator: %s\n", yytext);
}

/* Special Symbols */
"("|")"|"{"|"}"|";"|","
{
    printf("Delimiter: %s\n", yytext);
}

/* Ignore comments */
"//".*

/* Ignore spaces, tabs and newlines */
[ \t\n]+ ;

/* Invalid characters */
.
{
    printf("Invalid: %s\n", yytext);
}
%%

int yywrap()
{
    return 1;
}

int main()
{
    yylex();
    return 0;
}
