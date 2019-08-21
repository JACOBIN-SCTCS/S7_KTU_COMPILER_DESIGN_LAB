%{
	#include<stdio.h>
	#include <stdlib.h>
	#include<string.h>
	
	extern int yylex();
	void yyerror(char *s);
	
	struct astnode
	{
		char operator[20];
		struct astnode *left;
		struct astnode *right;	
	};
%}

%union
{
	char variable[20];
	struct astnode *node;
}

%start start
%left '+' '-' '*' '/' 
%token<variable> ID NUMBER
%type<node> expr 


%%
start : expr ';'  { generatepostorder($1); generateintercode(); exit(0); }
expr : expr '+' expr { $$ = makenode("+\0",$1,$3);	}	
     | expr '-' expr { $$ = makenode("-\0",$1,$3);	}
     | expr '*' expr { $$ = makenode("*\0",$1,$3);	}
     | expr '/' expr { $$ = makenode("/\0",$1,$3);	}
     | '(' expr ')   { $$ =$2;				}
     | ID 	     { $$ = makenode
%%

void yyerror(char *s)
{
	fprintf(stdout,"INVALID EXPRESSION\n");
}


int main()
{
	 yyparse();
}
