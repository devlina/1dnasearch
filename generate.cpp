#include<iostream>
#include<cstdlib>
#include<cstring>
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
	fputs("\\n\t",out);
	fputs(str2,out);
	fputs("\n.|\\n\n\n%%\n",out);
	fprintf(out,"extern FILE *yyin,*yyout;\nmain()\n{\nyyin=fopen(\"pattern\",\"r\");\nyyout=fopen(\"matched_motif\",\"w\");\n\nyylex();\n}");
	fclose(in);
	fclose(out);		
}

//read the matched motif strings and store them in vector.
bool get_matched_motif(vector<int>& str)
{
        
        int c,num=0;
         
        str.clear();  
        while((c=getc(fp))!=EOF)
        {
              
		if(isdigit(c))
                  num=num*10+(c-48);    
		else if(ispunct(c))
		{
			            
				str.push_back(num);
                           	num=0;
		}
		else if(c=='\n')
		{
			c=getc(fp);
			return true;
		}
                                    
		else continue;                              
                                                                  
        } 
        
       return false;                           
}

int main()
{
	
	
	generate_lexer("motif","mylexer.l");
	system("lex mylexer.l");
	system("gcc lex.yy.c -o match -ll");
	system("./match");
	vector<int> str;
  	fp=fopen("matched_motif","r");
  	if(fp==NULL)  fprintf(stderr,"cannot open file..");
   
  	while(get_matched_motif(str))
  	{
       		for(int i=0;i<str.size();i++)
        		cout<< str.at(i)<< ' ';
        	cout << "\n";    
	}
	return 0;
}
