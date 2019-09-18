#include<iostream>
#include<vector>
using namespace std;

class ENFA
{
	int number_of_states;
	int number_of_symbols;

	vector<vector<char>>  adjacency_matrix;

	ENFA(int no_of_states, no_of_symbols)
	{
		number_of_states = no_of_states;
		number_of_symbols = no_of_symbols;
	}

	void initialize()
	{
		boolean yes;
		int  symbol;

		for(int i=0;i<number_of_states;++i)
		{
			for(int j=0;j<number_of_states;++j)
			{
				cout << "Is there a transition from state"<<i<<"state"<<j<<"( 0 for no | 1 for yes)\n";
				cin >> yes;
				if(yes)
				{
					cout<<"Enter the input symbol (-1 for Epsilon)  0 for a likewise "<<"\n";
					cin>>symbol;
					if(symbol!=-1)
					{
						adjacency_matrix[i][j] = 'a'+symbol;

					}
					else
					{
						adjacency_matrix[i][j] = 'E';

					}
				}
				else
				{
					adjacency_matrix[i][j] = '0';
				}
			}
		}
	}

	void printDFA()
	{
		cout<<"Printing the DFA\n";
		for(int i=0;i<number_of_states;++i)
		{
			cout<<endl;
			for(int j=0;j<number_of_states;++j)
			{
				cout<<adjacency_matrix[i][j] << " "<<endl;
			}
		}
	}

}




int main()
{
	int number_of_states=3 ;
	int input_symbols=1;
	ENFA enfa(number_of_states,input_symbols);
	enfa.initialize();
	enfa.printDFA();
}
