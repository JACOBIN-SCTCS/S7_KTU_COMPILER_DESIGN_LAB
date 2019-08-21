%{
<<<<<<< HEAD
	#include<stdlib.h>
	#include<stdio.h>

	extern int yylex();
	void yyerror(char *s);
%}

%start start
%token NUMBER ID

%left '+' '-'
%left '*' '/'
%%

start : expr ';' 		{ printf("Valid arithmetic expression\n"); }

expr : NUMBER 
      | ID
      | expr '+' expr
      | expr '-' expr
      | expr '*' expr 
      | expr '/' expr 	
      | '(' expr ')'   {;}
=======

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
	;

>>>>>>> 94dab65e7ce9dc959256b7a26862fec46e56a5c3
%%

void yyerror(char *s)
{
<<<<<<< HEAD
 fprintf(stdout,"INVALID ARITHMETIC EXPRESSION");
=======
	fprintf(stdout,"Invalid expression\n");
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
