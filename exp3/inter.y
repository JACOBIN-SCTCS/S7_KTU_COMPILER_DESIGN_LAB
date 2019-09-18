%{

	#include<stdio.h>
	#include<stdlib.h>
	#include<string.h>

	extern int yylex();
	void yyerror(char *s);
	
	int tempcount=0;

	extern FILE *yyout;				
%}

%union
{
	char id[30];
}
%token<id> ID NUMBER 
%type<id> expr 

%left '-' '+'  
%left '*' '/'
%start start 

%%
start : ID '=' expr'\n' {	fprintf(yyout,"%s := %s\n",$1 , $3); fclose(yyout); exit(0);	}

expr : expr '+' expr	{ 	
     				tempcount+=1;
     				fprintf(yyout,"t%d := %s + %s\n",tempcount,$1,$3);	
				sprintf($$,"t%d",tempcount);
			}
     |	 expr '-' expr  {       
				tempcount+=1;
                                fprintf(yyout,"t%d := %s - %s\n",tempcount,$1,$3);
                                sprintf($$,"t%d",tempcount);
                        }
     |   expr '*' expr  {      
				tempcount+=1;
                                fprintf(yyout,"t%d := %s * %s\n",tempcount,$1,$3);
                                sprintf($$,"t%d",tempcount);
                        } 
      |  expr '/' expr  {       
				tempcount+=1;
                                fprintf(yyout,"t%d := %s / %s\n",tempcount,$1,$3);
                                sprintf($$,"t%d",tempcount);
                        }
     | '(' expr ')'	{
				tempcount+=1;
				fprintf(yyout,"t%d := %s\n",tempcount,$2);
				sprintf($$,"t%d",tempcount);
			}
     | '-' ID           {
				tempcount+=1;	
				fprintf(yyout,"t%d := -%s\n",tempcount,$2);
				sprintf($$,"t%d",tempcount);
			}
     | '-' NUMBER       {
				tempcount+=1;	
				fprintf(yyout,"t%d := -%s\n",tempcount,$2);
				sprintf($$,"t%d",tempcount);
			}

   

     | 	ID 		{;}
     |	NUMBER		{;}  


%%


void yyerror(char *s)
{
	fprintf(stdout,"Error generating code");
}

int main()
{
	yyout = fopen("output.txt","w");
	yyparse();
}

