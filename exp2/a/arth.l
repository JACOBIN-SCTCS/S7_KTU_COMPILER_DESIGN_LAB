%{
	#include "arth.tab.h"
	#include<stdio.h>
%}

%%
[0-9]+		{ return NUMBER ; }
[+|\-|*|/|;|(|)|%]	{ return *yytext; }
[a-z]+			{ return ID;      }
[A-Z]+			{ return ID;	  }

%%

int yywrap()
{
	return 1;
}
