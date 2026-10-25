%{
#include "y.tab.h"
%}

%%
[0-9]+              { return NUMBER; }
[a-zA-Z][a-zA-Z0-9]* { return ID; }
[+\-*/()]           { return yytext[0]; }
[ \t]               ;
\n                  { return 0; }
.                   { return yytext[0]; }
%%
