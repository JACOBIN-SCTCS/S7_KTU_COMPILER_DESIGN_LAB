%{

	#include<stdio.h>
	#include "validvar.tab.h"
%}

%%
[a-z]|[A-Z]:	{ return letter; }
[0-9]   {return digit ;  }
'\_'    { return *yytext;}
[\n]    { return *yytext;}

%%

int yywrap()
{

	return 1;
}


