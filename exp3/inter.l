%{
	#include <stdio.h>
	#include <stdlib.h>
	#include "inter.tab.h"
%}

%%
[a-z]+|[A-Z]+	{	strcpy(yylval.variable,yytext); return ID ; }
[0-9]+	 	{ 	strcpy(yylval.variable,yytext); return NUMBER; }
[+|\-|*|/|\(|\)]{       return *yytext; 		}
%%


int yywrap()
{
	return 1;
}
