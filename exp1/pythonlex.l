%{
	#include<stdio.h>
	#include<stdlib.h>


	FILE *fp;
%}

%%
	
"if"	 {   fprintf(fp," TOKEN<IF> ");			   }
"def" 	 {   fprintf(fp," TOKEN<DEF> ");  		   }
"else"   {   fprintf(fp," TOKEN<ELSE> ");		   }
"elif"   {   fprintf(fp," TOKEN<ELIF> ");	           }
"while"  {   fprintf(fp," TOKEN<WHILE> ");	           }
"range"  {   fprintf(fp," TOKEN<RANGE> ");		   }
"in"	 {   fprintf(fp," TOKEN<IN> ");			   }
"return" {  fprintf(fp," TOKEN<RET> ");			   }

[a-z]([a-z]|[0-9])*	  { fprintf(fp," TOKEN<IDENTIFIER> "); }
[+|-|*|%|/|=|(|)|:|<|<=|>=|>|==|\"] 		  { fprintf(fp,"TOKEN<%s> ",yytext);   } 

[0-9][0-9]* { fprintf(fp," TOKEN<NUMBER> " );		 	}
[\n]    {  fprintf(fp,"\n");					}

#(.*)\n	 {   				;		   }	
"if"	 {   fprintf(fp," TOKEN<IF> ");			   }
"def" 	 {   fprintf(fp," TOKEN<DEF> ");  		   }
"else"   {   fprintf(fp," TOKEN<ELSE> ");		   }
"elif"   {   fprintf(fp," TOKEN<ELIF> ");	           }
"while"  {   fprintf(fp," TOKEN<WHILE> ");	           }
"range"  {   fprintf(fp," TOKEN<RANGE> ");		   }
"in"	 {   fprintf(fp," TOKEN<IN> ");			   }
"return" {  fprintf(fp," TOKEN<RET> ");			   }

[a-z]([a-z]|[0-9])*	  { fprintf(fp," TOKEN<IDENTIFIER> "); }
[+|-|*|%|/|=|(|)|:|<|<=|>=|>|==] 		  { fprintf(fp,"TOKEN<%s> ",yytext);   } 

[0-9][0-9]* { fprintf(fp," TOKEN<NUMBER> " );		 	}
[\n]    {  fprintf(fp,"\n");					}

":exit" {   fclose(fp); exit(0); 			   }
		
%%

int main(int argc , char*argv[])
{
	fp = fopen("output.txt","w");
	yylex();
	

}

