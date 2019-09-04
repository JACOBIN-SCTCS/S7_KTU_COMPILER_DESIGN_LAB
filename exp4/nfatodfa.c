#include <stdio.h>

struct transition
{
	char currentstate;
	char inputsymbol;
	char nextstate[30];
}transitiontable;

void main()
{
	int numstates;
	int numinputs;
	int i;

	char states[30]	;
	char inputs[20];

	printf("\nENTER THE NUMBER OF STATES\n");
	scanf("%d",&numstates);
	printf("\nENTER THE NUMBER OF INPUT SYMBOLS\n");
	scanf("%d",&numinputs);

	//printf("Enter the States in Capital Letters\n");
	for(i=0;i<numstates;++i)
	{
		states[i] = 'A'+i;
	}
	for(i=0;i<numinputs;++i)
	{
		scanf("%c",inputs[i]);
	}
	printf("\n Enter the transition table \n ");




	return 0;
}
