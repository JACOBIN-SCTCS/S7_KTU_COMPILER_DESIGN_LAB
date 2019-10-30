#include<stdio.h>

void main()
{
	FILE *fp;
	FILE *out;
	char input_string[20];


	fp =fopen("inter.txt","r");
	out = fopen("program.asm","w");

	while(fp != NULL)
	{
		fscanf(fp,"%s",input_string);
		printf("%s\n",input_string);

	}
	fclose(fp);
	fclose(out);
}
