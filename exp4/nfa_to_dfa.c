#include<stdio.h>
#include<stdlib.h>
#include<string.h>


struct transition
{
	char symbol;
	char final_states[30];
};


struct states
{
	char state[30];
	int is_final;
	struct transition sym_transition[30];
} transition_table[30];


struct dfa_states
{
	char state[30];
	int bitvector[30];
	int is_final;
	struct transition sym_transition[30];
} dfa_table[30];


int n_states;
int n_symbols;
int epsilon_closure[30][30];

int dfa_table_count=0;

int final_states[30];
int final_states_dfa[30];

int belongs_to[30];

int partition[30][30];


void compute_epsilon_closure(char initial_state)
{
	char states[30];
	char stack[30];
	int top=-1;
	int index;
	char ele;
	int i,j;
	int second_state;

	int state = initial_state-'0';


	epsilon_closure[state][state] =1;
	///strcpy(states,transition_table[state].sym_transition[n_symbols-1].final_states);
	/*for(i=0;i<strlen(states);++i)
	{
		 index = states[i]-'0';
		 if(epsilon_closure[state][index] !=1)
		 {

		 	epsilon_closure[state][index]=1;
		 	top=top+1;
		 	stack[top]= states[i];
		}
	}
	*/

	top = top+1;
	stack[top]= initial_state;

	while(top>=0)
	{
		index = stack[top]-'0';
		top = top-1;

		strcpy(states,transition_table[index].sym_transition[n_symbols-1].final_states);
        	for(i=0;i<strlen(states);++i)
        	{
                	index = states[i]-'0';
			if(epsilon_closure[state][index]!=1)
			{
                 		epsilon_closure[state][index]=1;
                 		top=top+1;
                 		stack[top]= states[i];
			}
        	}

	}


}


void compute_transition(char state,char symbol,int enfa_nfa)
{
	int bitvector[30];
	int final_vector[30];
	char transitions[30];

	int  index = state-'0';
	int is_final,is_empty;
	int i=0,j=0;
	int flag=0;
	int in1,in2,in3;

	char underscore[2] ={'_' , '\0'};

	for(i=0;i<30;++i)
	{
		bitvector[i]=0;
		final_vector[i]=0;
	}

	for(i=0;i<n_states;++i)
	{
		if(dfa_table[index].bitvector[i]==1)
		{
			in1 = symbol-'a';
			strcpy(transitions,transition_table[i].sym_transition[in1].final_states);
			if(strcmp(transitions,underscore)!=0)
			{

				for(j=0;j<strlen(transitions);++j)
				{
					in2 = transitions[j] -'0';
					bitvector[in2] =1;
				}
			}
		}
	}



	for(i=0;i<n_states;++i)
	{
		if(bitvector[i]==1)
		{
			if(enfa_nfa)
			{

				for(j=0;j<n_states;++j)
				{
					final_vector[j] = final_vector[j]+ epsilon_closure[i][j];
				}
			}
			else
			{
					final_vector[j]=0;
					final_vector[i]=1;
			}
		}
	}


	for(j=0;j<n_states;++j)
	{
		if(final_vector[j] >=1)
			final_vector[j]=1;
		else
			final_vector[j]=0;
	}

	is_empty=0;
	for(j=0;j<n_states;++j)
	{
		if(final_vector[j]==1)
		{
				is_empty=1;
				break;
		}
	}

	flag=0;
	for(i=0;i<dfa_table_count;++i)
	{
		flag=1;
		for(j=0;j<n_states;++j)
		{
			if(final_vector[j]!= dfa_table[i].bitvector[j])
				{
					flag=0;
					break;
				}
		}
		if(flag==1)
		{
			in3=i;
			break;

		}
	}

	if(flag==1)
	{
		strcpy(dfa_table[index].sym_transition[in1].final_states, dfa_table[in3].state);
		dfa_table[index].sym_transition[in1].symbol= symbol;
	}
	else if(flag==0 && is_empty==0)
	{
		strcpy(dfa_table[index].sym_transition[in1].final_states, underscore);
		dfa_table[index].sym_transition[in1].symbol = symbol;

	}
	else
	{
		//dfa_table_count  = dfa_table_count + 1;
		dfa_table[dfa_table_count].state[0] = (char)(dfa_table_count + '0');
		dfa_table[dfa_table_count].state[1] ='\0';
		dfa_table[dfa_table_count].is_final=0;
		for(j=0;j<n_states;++j)
		{
			dfa_table[dfa_table_count].bitvector[j] = final_vector[j];
			if(final_vector[j] == final_states[j])
			{
				final_states_dfa[dfa_table_count]=1;
				dfa_table[dfa_table_count].is_final=1;
			}
		}



		strcpy(dfa_table[index].sym_transition[in1].final_states,dfa_table[dfa_table_count].state);
		dfa_table[index].sym_transition[in1].symbol= symbol;
		dfa_table_count  = dfa_table_count +1;

	}


}


void print_nfa()
{
	int i,j,k;
	printf("<---------------TRANSITION TABLE (NFA) ----------------->\n");
	for(j=0;j<n_symbols;++j)
	{

		if(j==(n_symbols-1))
		{
			printf("| \t E \t |\n");
		}
		else
		{
			printf("| \t %c \t |",(j+'a'));
		}
	}
	printf("-------------------------------------------------------------\n");
	for(i=0;i<n_states;++i)
	{
		if(transition_table[i].is_final)
		{
			printf("*q%c ",transition_table[i].state[0]);
		}
		else
		{
			printf("q%c ",transition_table[i].state[0]);

		}
		for(j=0;j<n_symbols;++j)
		{
			printf("|\t ");
			if (strcmp(transition_table[i].sym_transition[j].final_states,"_")==0)
			{
				printf("_");
			}
			else
			{
				for(k=0;k<strlen(transition_table[i].sym_transition[j].final_states) ; ++k)
				{
					printf("q%c",transition_table[i].sym_transition[j].final_states[k]);
				}
			}
			printf("\t|");

		}
		printf("\n");
	}
}



void print_dfa()
{
	int i,j,k;
	printf("\n\n<-------------------- TRANSITION TABLE (DFA)--------------------->\n");


	for(j=0;j<(n_symbols-1);++j)
        {

                  printf("| \t %c \t |",(j+'a'));
     	}
	printf("\n------------------------------------------------------------------------\n");
	for(i=0;i<dfa_table_count;++i)
        {
                if(dfa_table[i].is_final)
                {
                        printf("*q%c ",dfa_table[i].state[0]);
                }
                else
                {
                        printf("q%c ",dfa_table[i].state[0]);

                }
                for(j=0;j<(n_symbols-1);++j)
                {
                        printf("|\t ");
			if(strcmp(dfa_table[i].sym_transition[j].final_states,"_\0")==0)
			{
				printf("_");
			}
			else
			{
				for(k=0;k<strlen(dfa_table[i].sym_transition[j].final_states) ; ++k)
                        	{
                              	  	printf("q%c",dfa_table[i].sym_transition[j].final_states[k]);
                        	}
			}
                        printf("\t|");

                }
                printf("\n");
        }

}


void minimize_dfa()
{
	int i,j,k,l,flag;
	int temp_vector[30];
	int modified[30];
	int minimized_dfa_count=2;
	int previous_dfa_count=2;

	for(i=0;i<30;++i)
	{
		belongs_to[i]=0;
		temp_vector[i]=0;
		modified[i]=0;
		for(j=0;j<30;++j)
			partition[i][j]=0;
	}

	j=1;
	for(i=0;i<dfa_table_count;++i)
	{
		if(dfa_table[i].is_final !=0)
		{
			j=0;
			break;
		}
	}
	if(j!=0)
		return;

	for(i=0;i<dfa_table_count;++i)
	{
		if (dfa_table[i].is_final==0)
		{
			belongs_to[i] = 0;
			partition[0][i] =1;
		}
		else
		{
			belongs_to[i]=1;
			partition[1][i] =1;
		}
	}

	i=0;
	while(i<minimized_dfa_count)
	{
		for(j=0;j<dfa_table_count;++j)
		{
			temp_vector[j]=belongs_to[j];
			modified[j] =0;
		}
		flag=0;
		for(j=0;j<dfa_table_count;++j)
		{
			if(belongs_to[j]==1 &&modified[j]!=1)
			{
				for(k=j+1;(k<dfa_table_count &&modified[k] !=1) ;++k)
				{
					for(l=0;l<(n_symbols-1);++l)
					{
						if(belongs_to[dfa_table[j].sym_transition[l].final_states[0] -'0']  != belongs_to[dfa_table[k].sym_transition[l].final_states[0] -'0']  )
						{
									
								temp_vector[k]=minimized_dfa_count;
							        partition[minimized_dfa_count][k]=1;
								flag=1;	
						}
					
					
					}
				}
			}
		}
		if(flag==1)
		{
			minimized_dfa_count = minimized_dfa_count+1;
			for(j=0;j<dfa_table_count;++j)
			{
				if(belongs_to[j]!= temp_vector[j])
				{
					partition[i][j]=0;
				}


				belongs_to[j] =temp_vector[j];
			
			}

		}
		i=i+1;
	}

	for(i=0;i<dfa_table_count;++i)
	{
		printf("\n");
		for(j=0;j<dfa_table_count;++j)
		{
			printf("%d\t",partition[i][j]);	
		}
	}

}

void main()
{
	//int n_states;
	//int n_symbols;
	char filename[30];
	char temp_buffer[20];
	char state,symbol;
	int i,j;
	char temp;
	int ch;
	int counter;
	int enfa_nfa;

	FILE *fp;


	for(i=0;i<30;++i)
	{
		for(j=0;j<30;++j)
		{
			epsilon_closure[i][j]=0;
		}
	}

	for(i=0;i<30;++i)
	{
		final_states[i] = 0;
		final_states_dfa[i]=0;
	}

	
	printf("Enter the number of states\n");
	scanf("%d",&n_states);
	
	printf("Is it an Enfa(1) or nfa(0)\n");
	scanf("%d",&enfa_nfa);
	
	printf("Enter the number of input symbols including epsilon (In case of nfa leave final symbol same as state)\n");
	scanf("%d",&n_symbols);



	printf("Enter the name of the file holding the transition table\n");
	scanf("%s",filename);
	fp = fopen(filename,"r");
	if (fp==NULL)
	{
		printf("Filename not found\n");
		exit(0);
	}

	for(i=0;i<n_states;++i)
	{
		state = (char)'0'+i;
		printf("Is state q%c a final state\n",state);
		scanf("%d",&ch);
		if(ch==1)
		{
			transition_table[i].is_final=1;
			final_states[i] = 1;
		}
		else
		{
			transition_table[i].is_final=0;
			final_states[i]=0;
		}
		transition_table[i].state[0]=state;
		transition_table[i].state[1]='\0';
		for(j=0;j<n_symbols;++j)
		{
			fscanf(fp,"%s",temp_buffer);
			if(j==(n_symbols-1))
			{
				transition_table[i].sym_transition[j].symbol = 'E';
			}
			else
			{
				symbol = (char)'a'+j;
				transition_table[i].sym_transition[j].symbol = symbol ;
			}
			strcpy(transition_table[i].sym_transition[j].final_states,temp_buffer);

		}
	}


	for(i=0;i<n_states;++i)
	{
		//printf("\n %s  ",transition_table[i].state);

		compute_epsilon_closure(transition_table[i].state[0]);

		//for(j=0;j<n_symbols;++j)
		//{
		//	printf("\t%c : %s ",transition_table[i].sym_transition[j].symbol,transition_table[i].sym_transition[j].final_states);

		//}
	}

	print_nfa();
	fclose(fp);
	printf("\n");




	
	printf("Epsilon closure\n");
	for(i=0;i<n_states;++i)
	{
		printf("\n");
		for(j=0;j<n_states;++j)
		{
			printf("%d  ", epsilon_closure[i][j]);
		}
	}


	dfa_table[0].state[0]= '0';
	dfa_table[0].state[1] = '\0';
	for(i=0;i<n_states;++i)
	{
		if(enfa_nfa)
		{

			dfa_table[0].bitvector[i]= epsilon_closure[0][i];
			  if(final_states[i]==1)
                	{
                        	dfa_table[0].is_final=1;
                	}

		}
		else
		{
			dfa_table[0].bitvector[0]=1;
			dfa_table[0].bitvector[i]=0;
		}

	}


	dfa_table_count+=1;


	counter=0;
	while(counter<dfa_table_count)
	{

		//counter = counter+ 1;
		for(i=0;i<(n_symbols-1);++i)
		{
			        temp = (char) 'a'+i;
				compute_transition(  dfa_table[counter].state[0],temp,enfa_nfa);
		}
		counter = counter +1;
	}

       /* printf("\nTransition Table\n");
        for(i=0;i<dfa_table_count;++i)
        {
                printf("\n %s  ",dfa_table[i].state);
                //compute_epsilon_closure(transition_table[i].state[0]);
                for(j=0;j<(n_symbols-1);++j)
                {
                        printf("\t%c : %s ",dfa_table[i].sym_transition[j].symbol,dfa_table[i].sym_transition[j].final_states);

                }
        }*/
	print_dfa();

	minimize_dfa();

}
