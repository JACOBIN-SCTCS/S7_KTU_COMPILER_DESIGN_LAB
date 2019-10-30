#include<stdio.h>
#include<string.h>

char parse_string[30];
int pointer=0;
int flag=1;
int num_prod=8;

void S();
void W();
void T();
void X();
void F();


char str[8][30] = { "S->TW\0" , "W->+TW\0","W->#\0","T->FX\0","X->*FX\0","X->#\0","F->(S)\0","F->i\0" };



void S()
{
	T();
	W();
}


void W()
{
	if(parse_string[pointer] =='+')
	{
		pointer = pointer +1;
		T();
		W();
	}
	else
	{
		return;
	}
}

void T()
{
	F();
	X();
}

void X()
{
	if(parse_string[pointer]=='*')
	{
		pointer = pointer +1;
		F();
		X();
	}
	else
	{
		return ;
	}
}

void F()
{
	if(parse_string[pointer] == '(')
	{
		pointer = pointer +1;
		S();
		if(parse_string[pointer] ==')')
		{
			pointer = pointer+1;
		}
		else
		{
			return;
		}
	}
	else if(parse_string[pointer] =='i')
	{
		pointer = pointer +1;
	}
	else
	{
		flag=0;
	}
}


void main()
{
	int i=0;
	printf("The grammar for the parser\n");
	for(i=0;i<num_prod;++i)
	{
		printf("\t%s\n",str[i]);
	}

	printf("Enter the string which needs to be parsed\n");
	scanf("%s",parse_string);
	pointer =0;
	S();
	if(pointer == strlen(parse_string) && flag)
	{
		printf("Parsing succeeded\n");
	}
	else
	{
		printf("Parsing Failed\n");
	}
}
