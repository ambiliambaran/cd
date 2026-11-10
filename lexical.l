%{
    #include<stdio.h>
    int yywrap(){
        return 1;
    }
%}

%%

"int"|"float"|"char"|"if"|"else"|"for"|"while" {printf("%s : keyword\n",yytext);}

[a-zA-Z_][a-zA-Z0-9_]*   {printf("%s : identifier\n",yytext);}

[0-9]+ {printf("%s : constant\n",yytext);}

"+"|"-"|"*"|"/"|"="|"=="|"<"|">"  {printf("%s : operator\n",yytext);}

"("|")"|"{"|"}"|"["|"]" {printf("%s :special symbol\n",yytext);}

[ \t\n]+      ; 
.    {printf("%s : unknown symbol\n",yytext);}

%%

int main(){
    yylex();
    return 0;
}
