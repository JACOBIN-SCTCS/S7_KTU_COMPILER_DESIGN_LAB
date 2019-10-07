#include<stdio.h>
#include<string.h>
#include<stdlib.h>

char stack[50];
int top=-1;
char parse_string[30]="$";
int parse_string_length;

char precedence_table[8][8] = {


            /*         +    -   *   /   i   (   )   $  */

            /*  + */  '>', '>','<','<','<','<','>','>',

            /*  - */  '>', '>','<','<','<','<','>','>',

            /*  * */  '>', '>','>','>','<','<','>','>',

            /*  / */  '>', '>','>','>','<','<','>','>',

            /*  i */  '>', '>','>','>','=','=','>','>',

            /*  ( */  '<', '<','<','<','<','<','>','=',

            /*  ) */  '>', '>','>','>','=','=','>','>',

            /*  $ */  '<', '<','<','<','<','<','<','>',

};



char production[6][30]={"E->i\0","E->E+E\0","E->E-E\0","E->E*E\0","E->E/E\0","E->(E)\0"};
char handles[6][30] = { "i\0","E+E\0","E-E\0","E*E\0","E/E\0",")E(\0"};


int symbol_to_index(char symbol)
{
        int index;

        switch(symbol)
        {
                case '+' : index =0;
                           break;
                case '-' : index =1;
                           break;
                case '*' : index =2;
                           break;
                case '/' : index = 3;
                           break;
                case 'i' : index  =4;
                           break;
                case '(' : index = 5;
                            break;
                case ')' : index = 6;
                            break;
                case '$' : index = 7;
                           break;
        }
        return index;
}

void push(char symbol)
{
	top = top+1;
	stack[top] = symbol;

}

char  pop()
{

	if(top==-1)
	{
		return '_';
	}
	char topelement = stack[top];
	top=top-1;
	return topelement;


}

int reduce()
{
	int flag;
	int i,j,size;
	char ch;
	int new_top;

	for(i=0;i<6;++i)
	{
		size  = strlen(handles[i]);
		if(handles[i][0]==stack[top] && top+1 >=size)
		{
			flag=1;
			for(j=0;j<size;++j)
			{
				if(stack[top-j]!=handles[i][j])
				{
					flag=0;
					break;
				}
			}

			if(flag)
			{
				new_top = top-j+1;
				while(top != new_top )
				{
					ch = pop();
					if(ch=='_')
					{
						printf("Parsing Failed\n");
						exit(0);
					}

				}
				stack[top] = 'E';
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
	for(i=pointer;i<strlen(parse_string);++i)
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


char top_element()
{
	return stack[top];
}





void main()
{

	char temp[28];
	int i;
	int pointer=1;
	int pointer_index;
	int top_index;

	int production_index;

	printf("\nEnter the string to be parsed\n");
	scanf("%s",temp);
	strcat(temp,"$\0");
	strcat(parse_string,temp);
	parse_string_length = strlen(parse_string);


	push('$');

	printf("Operator Precedence Parsing\n");
	printf("|\t Input\t|\t Stack\t|\tAction\t\n");
	printf("________________________________________\n");
	while(pointer<parse_string_length)
	{
		push(parse_string[pointer]);
		pointer = pointer +1;
		print_string(pointer);
		print_stack();
		printf("|\t Shifted %c to the stack\t| \n",parse_string[pointer-1]);

		top_index = symbol_to_index(stack[top]);
		pointer_index = symbol_to_index(parse_string[pointer]);

		if(precedence_table[top_index][pointer_index]=='>')
		{
			while((production_index=reduce())!=-1)
			{
				print_string(pointer);
				print_stack();
				printf("|\t Reduction by Production %s\t| \n",production[production_index]);

			}
		}
	}
	if(top > 1 && stack[0]=='$' && stack[1]=='E' && stack[2]=='$')
	{
		printf("Parsing successful\n");
	}
	else
	{
		printf("Parsing Failed\n");
	}
}


