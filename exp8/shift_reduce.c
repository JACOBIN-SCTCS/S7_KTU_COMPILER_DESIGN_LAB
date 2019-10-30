#include<stdio.h>
#include<stdlib.h>
#include<string.h>


struct 
{
	char symbol;
	int numprod;
	int has_epsilon;
	char rhs[20][20];
} productions[20];

struct 
{
	char handle[20];
	char lhs;
} handles[20]  ;  


//char handles[20][20];


int handle_count=0;

char parse_string[30];
char stack[50];
int top=-1;



void shift(char a)
{
	top =top+1;
	stack[top] =a ;
	
}





void display_grammar(int n)
{
	int i,j;
	for(i=0;i<n;++i)
	{
		printf("%c -->  ",productions[i].symbol);

		for(j=0;j<productions[i].numprod;++j)
		{
			printf(" %s | ", productions[i].rhs[j]);
		}
		printf("\n");
	}

	printf("\n");


}


char pop()
{
	if (top==-1)
	{
		return '_';
	}
	char topelement = stack[top];
	top =top-1;
	return topelement;
}


int reduce()
{
	int i,size,flag=1,j,new_top;
	char ch;
	for(i=0;i<handle_count;++i)
	{
		size = strlen(handles[i].handle);
		if (handles[i].handle[0] == stack[top] && top+1 >=size )
		{
			flag=1;
			for(j=0;j<size;++j)
			{
				if(stack[top-j] != handles[i].handle[j])
				{
					flag=0;
					break;
				}
			}
			if(flag)
			{

				new_top = top-j+1;
				while(top != new_top)
				{
					ch = pop();
					
				}
				stack[top] = handles[i].lhs;
				return i;
			}

		}
	}
	return -1;
}


void print_string(int pointer)
{
	int i;
	printf("| \t");
	for(i=pointer;i<strlen(parse_string); ++i)
	{
		printf("%c",parse_string[i]);
	}
	printf("\t |");
}


void print_stack()
{
	int i;
	printf("| \t");
	for(i=0;i<=top;++i)
	{
		printf("%c",stack[i]);

	}
	printf("\t |");
}





void main()
{
	int n,i,j,k;
	FILE *fp;
	char prod[20];
	char temp;
	int prodindex;
	int start,end;
	int parse_string_length;
	int pointer;


	printf("Enter the number of Non Terminals in the grammar\n");
	scanf("%d",&n);


	/*
	 
		FORMAT OF PRODUCTIONS

		<NONTERMINAL>  <NO_OF_PRODUCTIONS> < PROD1> ,<PROD2> ,........<PROD n>

	 */	
	

	// 	INPUTTING SECTION
	//_______________________________________________________________


	fp  = fopen("productions.txt","r");

	for(i=0;i<n;++i)
	{
		fscanf(fp," %c", &productions[i].symbol);
		fscanf(fp,"%d",&productions[i].numprod);
		j=0;
		while(j<productions[i].numprod)
		{
			fscanf(fp,"%s",prod);
			if(strcmp(prod,"#\0")==0)
				productions[i].has_epsilon=1;

			strcpy(productions[i].rhs[j],prod);

			start =0 ; end = strlen(prod)-1;

			if(strcmp(prod,"#\0")!=0)
			{

				while(start<end)
				{
					temp = prod[start];
					prod[start] = prod[end];
					prod[end] = temp;
				
					start +=1;
					end -=1;
				
				}
				strcpy(handles[handle_count].handle,prod);
				handles[handle_count].lhs = productions[i].symbol;
				handle_count +=1;
			}
				
			j = j+1;
		}

	}

	fclose(fp);

	//________________________________________________________________
	//
	//

	display_grammar(n);

	printf("Enter the string which needs to be parsed\n");
	scanf("%s",parse_string);

	strcat(parse_string,"$");
	parse_string_length = strlen(parse_string);

	shift('$');

	pointer =0;

	while(pointer<parse_string_length)
	{

		shift(parse_string[pointer]);
		
		pointer = pointer +1;
		printf("\n");
		print_string(pointer);
		print_stack();
		
		printf("|\t Shifted %c to the stack \t\t|\n",parse_string[pointer-1] )	;

		while(   ( prodindex = reduce() )!=-1)
		{
			print_string(pointer);
			print_stack();
			printf("\t Reduction by production %c -->",handles[prodindex].lhs);
			for(k = strlen(handles[prodindex ].handle)  ; k>=0; k-=1 )
			{
				printf("%c",handles[prodindex].handle[k]);
			}
			printf("\t|\n");	
		}	
	}

	if(top>1 && stack[0]=='$' && stack[1]=='S' && stack[2]=='$')
	{
		printf("Parsing succeeded \n");

	}
	else
	{
		printf("Parsing Failed\n");
	}


}
