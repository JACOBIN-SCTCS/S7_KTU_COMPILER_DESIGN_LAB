%{
<<<<<<< HEAD
	#include "validvar.tab.h"
	#include <stdio.h>
%}

%%
[a-z]|[A-Z]	{ return LETTER; }
[0-9] 	 	{ return DIGIT;  }
[\n] 		{ return *yytext;}
=======
	#include<stdio.h>
	#include "validvar.tab.h"
%}

%%
[a-z]|[A-Z]:	{ return letter; }
[0-9]   {return digit ;  }
'\_'    { return *yytext;}
[\n]    { return *yytext;}
>>>>>>> 94dab65e7ce9dc959256b7a26862fec46e56a5c3
%%

int yywrap()
{
<<<<<<< HEAD
 return 1;
}
=======
	return 1;
}

>>>>>>> 94dab65e7ce9dc959256b7a26862fec46e56a5c3
