%{
#include <stdio.h>
#include <stdlib.h>

int yylex();
void yyerror(const char *s);
%}

%token NUMBER ID

%%

E : E '+' T
  | E '-' T
  | T
  ;

T : T '*' F
  | T '/' F
  | F
  ;

F : '(' E ')'
  | ID
  | NUMBER
  ;

%%

void yyerror(const char *s)
{
    printf("Invalid Arithmetic Expression\n");
}

int main()
{
    printf("Enter an arithmetic expression: ");

    if(yyparse() == 0)
        printf("Valid Arithmetic Expression\n");

    return 0;
}
