
mapping = {
		"+" : "ADD",
		"*" : "MUL",
		"/" : "DIV",
		"-" : "SUB"
	  }


def isnumber(n):
	try:
		float(n)
	except ValueError:
		return False
	return True


def main():
	
	file = open('inter.txt','r')
	out  = open('output.txt','w')	
	rhs_tokens =[] 
	

	register_map = {}
	variables = set()
	register_count =0 



	text = file.read()



	lines = text.split('\n')
	
	words = [ line.split(' ')  for line in lines]
	
	words.pop()

	print(words)
	for line in words:	
		if len(line) ==5:
			print(line[3] )
			
			if ( not line[2] in register_map.keys() )   :
				register_map[line[2]] = register_count
				register_count +=1
				out.write( "MOV R{} , {} \n".format(  register_map[line[2]] , line[2]   )  )
			
			if ( not line[4] in register_map.keys() )   :
                                register_map[line[4]] = register_count
                                register_count +=1
                                out.write( "MOV R{} , {} \n".format(  register_map[line[4]] , line[4]   )  )

			register_map [ line[0] ]  = register_count
			register_count +=1
			out.write( "MOV R{} , R{}\n".format(register_map [ line[0] ] , register_map [ line[2] ] ))
			out.write("{}  R{} , R{}\n".format( mapping[ line[3] ], register_map[line[0]] , register_map[line[4]]  ))
		
		elif len(line)==3:
			
			if( isnumber(line[2]) ):
				register_map[line[0]] = register_count
				register_count+=1
				out.write("MOV R{} , #{} \n".format(register_map[line[0]], line[2]))
			
			elif ( len(line[0])==1 ):
				out.write( "MOV {} , R{} \n".format( line[0], register_map[line[2]]))
			
			else:
				#out.write( "MOV R{} , R{} \n".format(  register_map[ line[0] ] , register_map[line[2]]  ) )

				if ( not line[0] in register_map.keys() )   :
                                	register_map[line[0]] = register_count
                                	register_count +=1
                          

				out.write( "MOV R{} , R{}\n".format(register_map[line[0]] ,register_map[line[2]] ))
							

	file.close()
	out.close()

if __name__ =='__main__':
	main()
