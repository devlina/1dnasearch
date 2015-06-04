#include "lca.h"
#include "settings.h"
#include <string>

//function object to compare two node numbers.
class compare_nodenum{
public:
	int operator()
	(const suffixtree_node* n1,const suffixtree_node* n2)
	{
		return n1->num < n2->num;
	}
};

int *H,*S,*U,*C;

/*this function compute the H,S,U and C values and store them in 
them in their respective arrays namely H[],S[],U[],C[].*/
void create_cv(suffixtree_node *stree,
				int no_of_identifier,
				bfslist_suffixtree & bfslist)
{
	
	int i;
	//store sorted list of leaves for all strings.
	map<int,vector<suffixtree_node*> > ordered_leaflist;
	vector<suffixtree_node*> leaflist;
	leaflist.clear();
	
	/*create the arrays.Each array have as many locations as the 
	number of nodes in the suffix tree*/
	H= (int*)malloc((suffixtree_node_count+1)*sizeof(int));
	S= (int*)malloc((suffixtree_node_count+1)*sizeof(int));
	U= (int*)malloc((suffixtree_node_count+1)*sizeof(int));
	C= (int*)malloc((suffixtree_node_count+1)*sizeof(int));

	
	// for each node initialize H value with 0.
	for(i=1;i<=suffixtree_node_count;i++)
		H[i]=0;
	
	// create ordered list L(i) of leaves with identifier i.
	for(BIT=bfslist.rbegin();BIT!=bfslist.rend();BIT++)
	{
		for(VT=(*BIT).begin();VT!=(*BIT).end();VT++)
		{
			if((*VT)->slink==null)
					
			ordered_leaflist[(*VT)->status.string_id].push_back(*VT);
		
		}
	}
	
	// sort the vectors inside the ordered list l for each string i.
	for(i=1;i<=no_of_identifier;i++)
	{
		leaflist=ordered_leaflist[i];
		stable_sort(leaflist.begin(),
					leaflist.end(),compare_nodenum());
		ordered_leaflist.erase(i);
		ordered_leaflist[i]=leaflist;
		leaflist.clear();
	}
	
	int size,cnt;
	suffixtree_node *w;
	
	/*compute lca for each consecutive pair of nodes in l(i) and 
	increment H(w) each time w is the computed lca*/
	for(i=1;i<=no_of_identifier;i++)
	{
		leaflist.clear();
		leaflist=ordered_leaflist[i];
		size=leaflist.size();
		for(cnt=0;cnt<size-1;cnt++)
		{
					
			w=calculate_lca(leaflist[cnt],leaflist[cnt+1]);
			H[w->num]++;
		}
		
	}
	//calculate S(v), U(v) and C(v).
	
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
				for(IT=(*VT)->children.begin();
						IT!=(*VT)->children.end();IT++)
				{
					S[(*VT)->num] += S[(*IT).second->num];
				}
				for(IT=(*VT)->children.begin();
						IT!=(*VT)->children.end();IT++)
				{
					U[(*VT)->num] += U[(*IT).second->num];
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


/*traverse the tree from root and retrieve the substrings of each 
nodes.substring of a node is its current substring attached with the 
parent node substring.Only the substrings of length at least critical 
length are displayed.*/	
	
void show_substrings(suffixtree_node *stree,
					vector<vector<int> >& combined_pattern)
{
	
	int tbeg,tend,stringid,i;
	string substring,parentstring;
	stack<suffixtree_node*> nodes; //store the nodes
	//stack<suffixtree_node*> parent;
	
	map<suffixtree_node*,string> node_value; 
	// holds the nodes and the substring of node
	root = stree;  //holds the root node for checking
	
	/*starting from the root nodes are pushed in the stack.once a 
	node is poped and string of its edge is stored in substring and
	string of its parent node is stored in parentstring and all its 
	children are pushed in the stack.The substring of any node is 
	formed by merging substring and parentstring.*/
	
	nodes.push(stree);
	while(!nodes.empty())
	{
		
		prev=nodes.top();
		nodes.pop();
		if(prev!=root)
		{
			//parent.pop();
			if(prev->slink != null && C[prev->num] >= 2)
			{
				RT=prev->label.rbegin();
				LST=RT->second.rbegin();
				stringid=RT->first;
				tbeg=LST->beg_index;
				tend=LST->end_index;
				substring="";
				i=tbeg;
				while(i<= tend)
				{
					/*fetch the characters from combined_pattern and 
					merge with substring*/
					substring += combined_pattern[stringid][i]+'0';
					i++;
				}
			
				//merge the nodes string with its parent node string
				if(prev->parent!=root)
				{
					parentstring = node_value[prev->parent];
					substring= parentstring + substring;
				}
				node_value[prev]= substring;
				if (substring.length()>= clen)
					cout << "\n" << substring;
			}
		}
		//push the children nodes in the stack
		for(CIT=prev->children.rbegin();
			CIT!=prev->children.rend();CIT++)
		{
			nodes.push((*CIT).second);
			//parent.push(prev);
		}
	}
	
}



