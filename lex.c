%{
#include <stdio.h>
%}

%%
"int"|"float"|"char"|"if"|"else"|"while"|"for"
                { printf("%s : Keyword\n", yytext); }

[a-zA-Z_][a-zA-Z0-9_]*
                { printf("%s : Identifier\n", yytext); }

[0-9]+
                { printf("%s : Number\n", yytext); }

"+"|"-"|"*"|"/"|"="|"=="|"<"|">"
                { printf("%s : Operator\n", yytext); }

";"|","|"("|")"|"{"|"}"
                { printf("%s : Special Symbol\n", yytext); }

[ \t\n]+        ;

.               { printf("%s : Unknown Symbol\n", yytext); }

%%

int main()
{
    yylex();
    return 0;
}
