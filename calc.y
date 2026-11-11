%{
  #include<stdio.h>
  #include<stdlib.h>

  int yylex(void);
  void yyerror(const char *s);
%}

%token NUMBER
%left '+' '-'
%left '*' '/'
%left UMINUS

%%

input:
     expr '\n'   {printf("Result = %d\n",$1);
                  YYACCEPT;
                  }
    ;

expr:
       expr '+' expr {$$=$1+$3;}
       | expr '-' expr {$$=$1-$3;}
       | expr '*' expr {$$=$1*$3;}
       | expr '/' expr {
              if($3==0){
                printf("Division by zero error\n");
                YYABORT;
              }
              $$=$1/$3;             
       }
       | '(' expr ')' {$$=$2;}
       | '-' expr  %prec UMINUS {$$=-$2;}
       | NUMBER    {$$ = $1;}
       ;

%%

void yyerror(const char *s){
    printf("Invalid Expression\n");
}

int main(){
    printf("Enter an arithmetic expression :\n");
    yyparse();
    printf("Parser finished\n");
    return 0;
}


