%{
#include <stdio.h>
int yylex(void);
void yyerror(const char *s);
%}

%token ID INVALID

%%
S : ID      { printf("Valid Variable\n"); }
  | INVALID { printf("Invalid Variable\n"); }
  ;
%%

void yyerror(const char *s)
{
    printf("Invalid Variable\n");
}

int main()
{
    printf("Enter a variable: ");
    yyparse();
    return 0;
}
