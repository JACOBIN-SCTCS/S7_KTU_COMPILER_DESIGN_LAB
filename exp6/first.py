

productions = ["S=TW","W=+TW","W=#","T=FX","X=*FX","X=#","F=(S)","F=i" ] 


first = None
follow = None
nonterminals = None
terminals = None


production_group = None
production_count = None
has_epsilon = None
rhs_contains = None


def initialization():
    global nonterminals 
    global terminals 
    global production_count
    global has_epsilon
    global production_group
    global rhs_contains

    nonterminals =set()
    terminals = set()
    production_count = {}
    production_group = {}
    has_epsilon = {}
    rhs_contains = {}

    for i in productions:
         
        if ( i[0] in production_count):
            production_count[i[0]] +=1
        else:
            production_count[i[0]] =1
        
        
        
        for j in i:
            if (j != '='):
                if j.isupper() and j.isalpha():
                    nonterminals.add(j)
                else : 
                    terminals.add(j)
    
    for i in nonterminals:
        production_group[i] = []
        rhs_contains[i] = set()



    for i in productions:
        production_group[i[0]].append(i)
        has_epsilon[i[0]] = 0
    
    for i in productions:
        for j in i[2:]:
            if j.isupper() and j.isalpha():
                rhs_contains[j].add(i)

    
    
    for i in productions: 
        if (i[2] == '#'):
            has_epsilon[i[0]] =1
    

    

def find_first( symbol):

    global terminals
    global production_group

    for i in production_group[symbol]:

        for j in range(2,len(i)):
            if i[j]=='#':
                break
            if ( not i[j].isupper()) and (i[j] in terminals) :
                first[symbol].add(i[j])
                break
            else:

                find_first(i[j])
                for k in first[i[j]]:
                    if k != '#':
                        first[symbol].add(k)
                if has_epsilon[i[j]] ==1:
                    continue
                else:
                    break

        if j==len(i)+1:
            has_epsilon[symbol]=1
            first[symbol].add('#')





    
def find_indices(symbol,production):

    present_list = [] 

    
    for word_index in range(2,len(production)):
        if symbol == production[word_index]:
            present_list.append(word_index)

    return present_list


def  find_follow(symbol):
    global rhs_contains

    for prod in rhs_contains[symbol]:
        for  i in  find_indices(symbol,prod):
                j=0
                flag=0
                for j in range(i+1,len(prod)):

                    if ( not prod[j].isupper()) and (prod[j] in terminals):
                        follow[symbol].add(prod[j])
                        break

                    else:
                        for k in first[prod[j]]:
                            if k !='#':

                                follow[symbol].add(k)
                        
                        find_follow(prod[j])

                        for k in follow[prod[j]]:
                            follow[symbol].add(k)

                        if has_epsilon[prod[j]]==1:
                            continue
                        else:
                            break
                    if j==len(prod)-1:
                        flag=1

                if flag==1or i==len(prod)-1:

                    if (not prod[0]==symbol) or  ( not prod[len(prod)-1] ==symbol )  :
                        find_follow(prod[0])

                        for l in follow[prod[0]]:
                            follow[symbol].add(l)
                        for l in follow[symbol]:
                            follow[prod[0]].add(l)

                


def print_results():
    

    print("FIRST SET OF GRAMMAR SYMBOLS \n")
    print("_______________________________\n")
    for i in nonterminals:
        print( str(i) + "---> " + str(first[i]))
    print("\n\nFOLLOW SET OF GRAMMAR SYMBOLS \n")
    print("_____________________________________\n")
    for i in nonterminals:
        print( str(i) + "---> " + str(follow[i]))


    
def main():

    global first 
    global follow
    global nonterminals
    global terminals

    first = {}
    follow = {}
    
    
    initialization()
    for i in nonterminals : 
        first[i] = set()
        follow[i] = set()

    
    follow['S'].add('$')

    for  i in has_epsilon.keys():
        if has_epsilon[i]==1:
            first[i].add('#')



    for i in nonterminals:
        find_first(i)

    for i in nonterminals:
        find_follow(i)


    print_results()


if __name__ =="__main__":
    main()

