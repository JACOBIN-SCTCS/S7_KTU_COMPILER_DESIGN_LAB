<<<<<<< HEAD
%{	
	#include<stdio.h>
	#include<stdlib.h>
	
	extern int yylex();
	void yyerror(char *s);

%}

%token LETTER DIGIT 
%start start

%%

start : variable {  printf("Valid variable definition\n"); exit(0);	}

variable : LETTER postcondn {;}

postcondn : LETTER postcondn
	  | DIGIT postcondn 
	  | '\n'   {;}

%%

void yyerror(char *s)
{
	fprintf(stdout,"Invalid variable definition\n");
=======
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
>>>>>>> 94dab65e7ce9dc959256b7a26862fec46e56a5c3
}

int main()
{
<<<<<<< HEAD
	yyparse();
=======
yyparse();
>>>>>>> 94dab65e7ce9dc959256b7a26862fec46e56a5c3
}
