%{
    #include "y.tab.h"
%}
%option noyywrap
%%

[a-zA-Z_][a-zA-Z0-9_]* {return ID;}
[^\n]+   {return INVALID;}
\n   {return 0;}

%%

