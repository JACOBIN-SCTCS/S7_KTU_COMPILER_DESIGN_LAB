%{
	#include<stdio.h>
	#include "inter.tab.h"
%}

%%
[0-9]+	{ strcpy(yylval.id,yytext); return NUMBER; }
[a-z]+	{ strcpy(yylval.id,yytext); return ID;	   }
[+|\-|*|\/|(|)|\=]	{ return *yytext;	}
[\n]			{ return *yytext;	}
%%

int yywrap()
{
	return 1;
}
