%{
	#include<stdio.h>
	#include<stdlib.h>
	extern int yylex();
	void yyerror(char *s);
%}

%token letter digit 
%start start 

%%

start : variable {  printf("Valid variable definition"); exit(0); }

variable : letter postcondn	{;}
	 | '_' postcondn	{;}

postcondn : '\n'  {;} 
	   | digit postcondn {;}
	   |letter postcondn {;}
	   ;

%%


void yyerror(char *s)
{
	fprintf(stdout,"Invalid Arithmetic expression");
}

int main()
{
	yyparse();
}
