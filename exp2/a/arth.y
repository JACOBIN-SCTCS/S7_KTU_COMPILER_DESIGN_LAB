%{

	#include<stdio.h>
	#include<stdlib.h>

	extern int yylex();
	void yyerror(char *s);

%}

%start start
%token NUMBER ID 

%left '+' '-'
%left '*' '/'
%left '%'

%%
start : exp ';'    { printf("Valid arithmetic expression\n"); exit(0); } 

exp :   NUMBER 	   {;}
    	| ID	   {;}
	| exp '+' exp  {;}
	| exp '-' exp  {;}
	| exp '*' exp  {;}
	| exp '/' exp  {;}
	| '(' exp ')'  {;}
	| exp '%' exp  {;}
	| '-' exp      {;}
	;

%%

void yyerror(char *s)
{

	fprintf(stdout,"Invalid expression\n");

}

int main()
{

	yyparse();
}
