#include<stdio.h>

int main()
{
	char NFA[30][30];
	int input_symbols , input_symbol;
	int number_of_states;
	int i,j,yes;


	int epsilon_closure[30][30];


	printf("Enter the number of states in the EPSILON-NFA\n");
	scanf("%d",&number_of_states);
	printf("Enter the number of input symbols\n");
	scanf("%d",&input_symbols);



	for(i=0;i<number_of_states;++i)
	{
		for(j=0;j<number_of_states;++j)
		{
			printf("Is there an edge from state q%d to state q%d (0 = no | 1= yes ) \n",i,j );
			scanf("%d",&yes);
			if(yes)
			{
				invalid_label:
				printf("Enter the edge symbol in (-1 for epsilon )");
				scanf("%d",&input_symbol);
				if(input_symbol > input_symbols)
				{
					printf("Enter a valid input symbol\n");
					goto  invalid_label;
				}
				if(input_symbol==-1)
					NFA[i][j] = 'E';
				else
					NFA[i][j] = 'a'+input_symbol ;
			}
			else
			{
				NFA[i][j] = '0';
			}
		}
	}

	for(i=0;i<number_of_states;++i)
	{
		printf("\n");
		for(j=0;j<number_of_states;++j)
		{
			printf(" %c ", NFA[i][j]);
		}

	}
return 0;

}
