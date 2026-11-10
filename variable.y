%{
#include <stdio.h>
int yylex(void);
void yyerror(const char *s);
%}

%token ID INVALID

%%

S : ID '\n'       { printf("Valid Variable\n"); }
  | INVALID '\n'  { printf("Invalid Variable\n"); }
  ;

%%

void yyerror(const char *s){
}

int main()
{
    printf("Enter a Variable: ");
    yyparse();
    return 0;
}
