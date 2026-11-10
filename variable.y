%{
    #include<stdio.h>
    int yylex(void);
    void yyerror(const char *s);
%}

%token ID INVALID

%%

S : ID  {printf("Valid Variable\n");}
   | INVALID  {printf("Invalid Variable\n");}
   ;

%%

void yyerror(const char *s){
}

int main(){
    printf("Enter a Variable :");
    yyparse();
    return 0;
}
