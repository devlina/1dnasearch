#include <iostream>
#include <cstdlib>
#include <vector>


using namespace std;

static FILE *in;

bool get_matchpos(vector<int>& str)
{
        
        int c=0,num=0,fwd;
         
        //if(feof(in)) return false;
        str.clear();
        //c=getc(in);  
        while((c=getc(in))!=EOF)
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
                       c=getc(in);
                      return true;
                  }
              
    	     
                                       
              //else continue;                                               
                                                               
        } 
       
	
           return false;
             
                          
}

int main()
{
   vector<int> str;
   in=fopen("strings","r");
   if(in==NULL)  fprintf(stderr,"cannot open %s file..");
   
   while(get_matchpos(str))
   {
         for(int i=0;i<str.size();i++)
             cout<< str.at(i)<< ' ';
         cout << "\n";    
   }
    fclose(in);
    
    return 0;      
}    
