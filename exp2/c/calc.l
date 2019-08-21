%{
	#include "calc.tab.h"
<<<<<<< HEAD
	#include<stdio.h>
%}

%%
[0-9]+		{ yylval.integer = atoi(yytext); return NUMBER;	}
[+\-*/\(\)%;]    { return *yytext; }
=======
	#include <stdio.h>
	#include <stdlib.h>
%}

%%
[0-9]+	{ 
	  yylval.integer = atoi(yytext);
	  return NUMBER ; 
	}
[+|/|\-|*|\%|(|)|;] { return  *yytext ; }	

>>>>>>> 94dab65e7ce9dc959256b7a26862fec46e56a5c3
%%

int yywrap()
{
<<<<<<< HEAD
	return 1;
=======
	return 1; 
>>>>>>> 94dab65e7ce9dc959256b7a26862fec46e56a5c3
}
