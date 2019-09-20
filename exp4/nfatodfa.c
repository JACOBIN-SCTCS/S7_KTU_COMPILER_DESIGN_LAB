#include<stdio.h>

struct enfa_state
{
	int state ;
	char symbol;
	struct enfa *next;
} *nfa[30];


void main()
{
	int i;
	int num_states , num_symbols;
	for(i=0;i<30;++i)
	{
		nfa[i] = NULL;
	}

	scanf("%d%d",&num_states, &num_symbols);
	for(i=0;i<num_states;++i)
	{
		nfa[i] = (struct enfa_state*)malloc(sizeof(struct enfa_state));
		nfa[i] -> state = i;
		nfa[i] -> symbol ='_';
		nfa[i] -> next =NULL;
	}



}
