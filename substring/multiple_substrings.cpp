#include "lca.h"
#include <string>

/*typedef vector<suffixtree_node *> leafnodes;
leafnodes *ordered_leaflist;*/
void show_substring(suffixtree_node *stree,vector<vector<int> >& pattern,int *C);

class compare_nodenum{
public:
	int operator()(const suffixtree_node* n1,const suffixtree_node* n2)
	{
		return n1->num < n2->num;
	}
};

int *H= (int*)malloc((suffixtree_node_count+1)*sizeof(int));
int *S= (int*)malloc((suffixtree_node_count+1)*sizeof(int));
int *U= (int*)malloc((suffixtree_node_count+1)*sizeof(int));
int *C= (int*)malloc((suffixtree_node_count+1)*sizeof(int));

void create_cv(suffixtree_node *stree,int no_of_identifier,bfslist_suffixtree & bfslist)
{
	
	int i;
	map<int,vector<suffixtree_node*> > ordered_leaflist;
	vector<suffixtree_node*> leaflist;
	leaflist.clear();

	
	
	
	// for each node initialize H value with 0.
	for(i=1;i<=suffixtree_node_count;i++)
		H[i]=0;
	
	// create ordered list L(i) of leaves with identifier i.
	for(BIT=bfslist.rbegin();BIT!=bfslist.rend();BIT++)
	{
		for(VT=(*BIT).begin();VT!=(*BIT).end();VT++)
		{
			if((*VT)->slink==null)
			{
				
				ordered_leaflist[(*VT)->status.string_id].push_back(*VT);
			}
		}
	}
	
	// sort the vectors inside the ordered list L(i)
	for(i=1;i<=no_of_identifier;i++)
	{
		leaflist=ordered_leaflist[i];
		stable_sort(leaflist.begin(),leaflist.end(),compare_nodenum());
		ordered_leaflist.erase(i);
		ordered_leaflist[i]=leaflist;
		leaflist.clear();
	}
	
	int size,cnt;
	suffixtree_node *w;
	//compute lca for each consecutive pair in L(i) and increment H(w) each time w is the lca
	for(i=1;i<=no_of_identifier;i++)
	{
		//size=ordered_leaflist[i].size();
		leaflist.clear();
		leaflist=ordered_leaflist[i];
		size=leaflist.size();
		for(cnt=0;cnt<size-1;cnt++)
		{
					
			w=calculate_lca(leaflist[cnt],leaflist[cnt+1]);
			H[w->num]++;
		}
		
	}
	//calculate S(v)
	
	for(BIT=bfslist.rbegin();BIT!=bfslist.rend();BIT++)
	{
		for(VT=(*BIT).begin();VT!=(*BIT).end();VT++)
		{
			S[(*VT)->num]=0;
			U[(*VT)->num]=0;
			if((*VT)->slink==null)
			{
				 S[(*VT)->num]=1;
				 U[(*VT)->num]=0;
				 C[(*VT)->num]=0;
			}
			else 
			{
				for(IT=(*VT)->children.begin();IT!=(*VT)->children.end();IT++)
				{
					S[(*VT)->num] += S[(*IT).second->num];
				}
				for(IT=(*VT)->children.begin();IT!=(*VT)->children.end();IT++)
				{
					U[(*VT)->num] += U[(*IT).second->num];//+ H[(*IT).second->num];
				}
				U[(*VT)->num] += H[(*VT)->num];
				C[(*VT)->num]= S[(*VT)->num]- U[(*VT)->num];
				
			}
		}
	}
	
	cout << "H values\n";
	for(i=1;i<=suffixtree_node_count;i++)
	 cout << H[i] << endl;
	 
	cout << "S values\n";
	for(i=1;i<=suffixtree_node_count;i++)
	 cout << S[i] << endl;
	
	cout << "U values\n";
	for(i=1;i<=suffixtree_node_count;i++)
	 cout << U[i] << endl;
	 
	cout << "C values\n";
	for(i=1;i<=suffixtree_node_count;i++)
		cout << C[i] << endl;
}

char *substring_temp;
	bool gotstring;
	int tbeg,tend,stringid;
char *substring= new char[1];
	
void show_substring(suffixtree_node *stree,suffixtree_node *root,vector<vector<int> >& pattern,int *C)
{
	
	if(stree!=root)
	{
	if(stree->slink!= null && C[stree->num]>=2)
	{
			
		temp=stree;
		while(temp!=root)
		{
			RT=temp->label.rbegin();
			LST=RT->second.rbegin();
			stringid=RT->first;
			tbeg=LST->beg_index;
			tend=LST->end_index;
			substring_temp=(char*)pattern[stringid][beg];
			while(beg <= end)
			strcat(substring_temp,(char*)pattern[stringid][++beg]);
			strcat(substring_temp,substring);
			temp=temp->parent;
		}
		cout << "\n" << substring << endl;
	}
	}
	
	for(IT=stree->children.begin();IT!=stree->children.end();IT++)
					
			show_substring((*IT).second,pattern,C);
		
}


int main()
{
	int str[6]={1,2,3,1,2,-1};
	int str1[7]={3,2,3,1,3,2,-2};
	//int str[12]={1,2,3,3,2,3,3,2,4,4,2,-1};
	vector<vector<int> > pattern;
	vector<int> vec;
	suffixtree_node *sft;
	bfslist_suffixtree bfslist;
	//int num=1;
	for(int i=1;i<=6;i++) vec.push_back(str[i-1]);
	pattern.push_back(vec);
	vec.clear();
	for(int i=1;i<=7;i++) vec.push_back(str1[i-1]);
	pattern.push_back(vec);
	sft=create_stree(pattern);
	bfs(sft,bfslist);
	cout << "nodes : " << suffixtree_node_count<< endl;
	preprocess_suffixtree(sft,bfslist);
	create_cv(sft,pattern.size(),bfslist);
	cout << "\nThe matching statistics is shown below.....\n";
	show_substring(sft,sft,pattern,C);
	free(H);
	free(S);
	free(U);
	free(C);
	return 0;
}	

