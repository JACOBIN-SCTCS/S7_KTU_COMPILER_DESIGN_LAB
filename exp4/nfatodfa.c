#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct enfa_state
{
	int state ;
	char symbol;
	struct enfa_state *next;
} *nfa[30] ;


void add_enfa_node(int start_state, char symbol,int end_state)
{
	struct enfa_state *ptr = nfa[start_state]->next;
	struct enfa_state *newnode  = (struct enfa_state*)malloc(sizeof(struct enfa_state));

	if(ptr==NULL)
	{
		newnode -> state = end_state;
        	newnode -> symbol = symbol;
        	newnode -> next =NULL;
        	nfa[start_state]-> next = newnode;

	}
	while(ptr->next !=NULL)
	{
		ptr = ptr-> next;

	}

	newnode -> state = end_state;
	newnode -> symbol = symbol;
	newnode -> next =NULL;
	ptr -> next = newnode;

}



void printtable(int num_states)
{
	struct enfa_state *ptr ;
	int i;


	for(i=0;i<num_states;++i)
	{
		ptr = nfa[i];
		printf(" FROM STATE %d\n", ptr->state);
		ptr = ptr -> next;

		while(ptr!=NULL)
		{

			printf("%c ------>  %d\n",ptr->symbol , ptr->state);
			ptr = ptr ->next;
		}
	}
}


void main()
{
	int i;
	int num_states , num_symbols,continue_flag;
	int start_state;
	char symbol ;
	int end_state;


	for(i=0;i<30;++i)
	{
		nfa[i] = NULL;
	}

	scanf("%d%d",&num_states, &num_symbols);
	//printf("num_states = %d",num_states);
	for(i=0;i<num_states;++i)
	{
		nfa[i] = (struct enfa_state*)malloc(sizeof(struct enfa_state));
		nfa[i] -> state = i;
		nfa[i] -> symbol ='_';
		nfa[i] -> next =NULL;
	}

	while(1)
	{
		scanf("%d" , &continue_flag);
		if(continue_flag==2)
			break;
		scanf("%d",&start_state);
		scanf("%c",&symbol);
		//printf("%c",symbol);
		scanf("%d",&end_state);
		add_enfa_node(start_state,symbol,end_state);

	}

	printtable(num_states);

}
