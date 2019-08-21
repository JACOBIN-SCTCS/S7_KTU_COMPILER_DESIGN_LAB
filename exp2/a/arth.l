%{
<<<<<<< HEAD
	#include<stdio.h>
	#include "arth.tab.h"
%}

%%

[0-9]+	{ return NUMBER;  }
[a-z]+ | [A-Z]+	{ return ID; }
[+\-*/\(\) ;] 	{ return *yytext; }

%%
=======
	#include "arth.tab.h"
	#include<stdio.h>
%}

%%
[0-9]+		{ return NUMBER ; }
[+|\-|*|/|;|(|)|%]	{ return *yytext; }
[a-z]+			{ return ID;      }
[A-Z]+			{ return ID;	  }

%%

>>>>>>> 94dab65e7ce9dc959256b7a26862fec46e56a5c3
int yywrap()
{
	return 1;
}
