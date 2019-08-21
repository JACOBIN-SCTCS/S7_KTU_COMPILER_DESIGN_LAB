%{
	#include<stdio.h>
<<<<<<< HEAD
	#include<stdlib.h>
=======
	#include <stdlib.h>

>>>>>>> 94dab65e7ce9dc959256b7a26862fec46e56a5c3
	extern int yylex();
	void yyerror(char *s);
%}

<<<<<<< HEAD
%start start

%union
{
int integer ;
}

%left '+' '-'
%left '*' '/' '%'
%type<integer> expr 
%token<integer> NUMBER

%%
start : expr ';' 	{ printf("RESULT=%d\n",$1); exit(0); 	}

expr : expr '+' expr	{ $$ =$1+$3;	}
     | expr '-' expr    { $$ =$1-$3;	}
     | expr '*' expr    { $$ =$1*$3;	}
     | expr '/' expr    { $$ = $1/$3;	}
     | '(' expr ')'	{ $$ =$2;	}
     | NUMBER  		{ $$=$1;	}
	
%%

void yyerror(char *s)
{
fprintf(stdout, "INVALID ARITHMETIC EXPRESSION\n");
=======
%union{
	int integer ;
}
%token<integer> NUMBER 
%start start 
%type<integer> expr;

%left '+' '-'
%left '*' '/' '%'


%%
 start : expr ';' {  printf("Result = %d\n",$1); exit(0); }

 expr  : expr '+' expr  { $$= $1+$3;  }
	| expr '-' expr { $$ =$1-$3;  }
	| expr '*' expr { $$ = $1*$3; } 
        | expr '/' expr { $$ =$1/$3;  }
	| '(' expr ')'  { $$ =$2;     }
	| expr '%' expr { $$ =$1%$2;  }
	| NUMBER 	{ $$=$1;      }
	
%%	

void yyerror(char *s)
{
 fprintf(stdout,"INVALID SYNTAX");
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
