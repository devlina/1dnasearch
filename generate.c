#include<stdio.h>
#include<stdlib.h>
#include<string.h>


// take the motifs from motif file and autogenerate the lexfile
void generate_lexer(char *mtfl,char *lxfl)
{
	FILE *in,*out;
	in=fopen(mtfl,"r");
	out=fopen(lxfl,"w");
	
	char str1[100]="{fprintf(yyout,\"";
	char str3[100]="\");}";
	char str2[100]="{fprintf(yyout,\"\\n\");}";
	//char *num="";
	int c,num;
	
	fputs("%%\n\n[\\t ]+;\n\n",out);
	//num="";
	while((c=getc(in))!=EOF)
	{
		if(c=='.') continue;		
		if(isdigit(c))  
		{
			num=c-48;		
			if(isdigit(c=getc(in)))
				num=num*10+(c-48);
			else ungetc(c,in);			
		}
		else if(c=='\n') 
		{
			fputs("\t",out);
			fputs(str1,out);
			fprintf(out,"%d,",num);
			fputs(str3,out);
			fputs("\n",out); 			
		}
		else putc(c,out);
	}
	fputs("\\n\t",out);
	fputs(str2,out);
	fputs("\n.|\\n\n\n%%\n",out);
	fprintf(out,"extern FILE *yyin,*yyout;\nmain()\n{\nyyin=fopen(\"pattern\",\"r\");\nyyout=fopen(\"strings\",\"w\");\n\nyylex();\n}");
	fclose(in);
	fclose(out);		
}

int main()
{
	
	/*if(argc==1 || argc==2)
	{
		printf("improper arguments..");
		exit(1);
	}*/
	generate_lexer("motif","mylexer.l");
	system("lex mylexer.l");
	system("gcc lex.yy.c -o match -ll");
	system("./match");
	return 0;
}
