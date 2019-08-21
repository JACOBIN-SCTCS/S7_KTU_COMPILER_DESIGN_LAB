%{
	#include<stdio.h>
	#include<stdlib.h>
	#include<string.h>

	extern int yylex();
	void yyerror(char *s);


	
	struct astnode 
	{
		char operand[20];
		struct astnode *left; 
		struct astnode *right;
	};
	
	struct astnode *makenode(char operator[20],struct astnode *left ,struct astnode *right);
	void printtree(struct astnode *root);
%}

%union	
{
	char  variable[20];
	struct astnode *node;
}

%start start 
%left '+' '-' '/' '*'
%type<node> expr
%token<variable> NUMBER ID

%%
start : expr ';'   { printtree($1); exit(0); }

expr : expr '+' expr  { $$ = makenode("+\0",$1,$3); }
     | expr '-' expr  { $$ = makenode("-\0",$1,$3); }
     | expr '*' expr  { $$ = makenode("*\0",$1,$3); }
     | expr '/' expr  { $$ = makenode("/\0",$1,$3); }
     | '(' expr ')'   { $$ = $2;		    }
     | NUMBER 	      { $$ = makenode($1,NULL,NULL); } 
     | ID	      { $$ = makenode($1,NULL,NULL); }
     ;
%%


struct astnode *makenode(char operator[20],struct astnode *left, struct astnode *right )
{	
	struct astnode *newnode = (struct astnode *)malloc(sizeof(struct astnode));
	strcpy(newnode-> operand,operator);
	newnode -> left = left;
	newnode -> right = right;
	return newnode; 	
}


void printtree(struct astnode *root)
{
	if(root==NULL)
		return ;
	
	/*if(root->left==NULL && root->right==NULL)
	{
		        printf("%s",root->operand);
	}
	else
	{*/
	printf("("); 
	
	printf("%s",root->operand);
	printtree(root->left);
	
	printtree(root->right);
	printf(")");
	/*}*/

}
void yyerror(char *s)
{
	fprintf(stdout,"INVALID SYNTAX\n");
}

int main()
{
	yyparse();
}

