#include<iostream>
#include<cstdlib>
#include <cstring>
#include <vector>

using namespace std;
static FILE *fp;

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
//	fputs("\\n\t",out);
//	fputs(str2,out);
//	fputs("\n.|\\n\n\n%%\n",out);
	fputs("\n.\n%%\n",out);
	
	fprintf(out,"extern FILE *yyin,*yyout;\nmain()\n{\nyyin=fopen(\"pattern\",\"r\");\nyyout=fopen(\"matched_motif\",\"w\");\n\nyylex();\n}");
	fclose(in);
	fclose(out);		
}

//read the matched motif strings and store them in vector.
bool get_matched_motif(vector<int>& str)
{
	int c,num=0, flag=0;

	if(feof(fp)!=0)
		return false;
	
	str.clear();  
	
	while((c=getc(fp))!='\n' && !feof(fp) )
	{
		flag = 1;
		
		if(isdigit(c))
			num=num*10+(c-48);    
		if(ispunct(c))
		{
			c=getc(fp);			
			if(isdigit(c))   
			{
				str.push_back(num);
				num=0;
			}
			ungetc(c,fp);
		}
		else continue;                                               
	} 

	if(c=='\n' && flag==1)
	{
		str.push_back(num);
	}

	return true;
}

int devlina_main()
{
	
	/*if(argc==1 || argc==2)
	{
		printf("improper arguments..");
		exit(1);
	}*/
	generate_lexer((char *)"motif",(char *)"mylexer.l");
	system("lex mylexer.l");
	system("gcc lex.yy.c -o match -ll");
	system("./match");
	vector<int> str;
  	fp=fopen("matched_motif","r");
  	if(fp==NULL)  fprintf(stderr,"cannot open file..");
   
/* not reqd in final program
  	int i=0;
  	while(get_matched_motif(str))
  	{
       		printf("%d\t%d\t",++i,str.size());
       		for(int i=0;i<str.size();i++)
				cout<< str.at(i)<< ' ';
        	cout<<"\n";
	}
	return 0;
*/
}
