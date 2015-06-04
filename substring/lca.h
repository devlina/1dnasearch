#include <cstdlib>
#include <stack>
#include <algorithm>
#include <functional>
#include <cmath>
#include "suffixtree5.h"
//#define largest_num pow(2.0,32.0)-1;
typedef struct{
	int h;
	int I;
	int A;
	suffixtree_node *L;
	int H;
	int string_depth;
	int S;
	int U;
	int C;
}lca_info;

//lca_info lca_values[suffixtree_node_count];
const int largest_num=(int)pow(2.0,32.0)-1;
lca_info *lca_values;
int l,Iw,k;
//children having maximum h value
/*class maxh{
public:
	bool operator()(suffixtree_node* a,suffixtree_node* b)

	{
		return(lca_values[a->num].h < lca_values[b->num].h);
		
	}
};

//children having maximum h(I(v)) value
class max_Ih {
public:
	bool operator()(suffixtree_node *a,suffixtree_node *b)const

	{
		return(lca_values[lca_values[a->num].I].h < lca_values[lca_values[b->num].I].h);
	}
};*/

/*typedef struct{
	int k;
	suffixtree_node *child;
}childpair;

bool maxh(std::pair<const int,suffixtree_node *a>,std::pair<const int,suffixtree_node *b>)
{
	return(lca_values[a->num].h < lca_values[b->num].h);
}

bool max_Ih(<int,suffixtree_node *a>,<int,suffixtree_node *b>)
{
	return(lca_values[lca_values[a->num].I].h < lca_values[lca_values[b->num].I].h);	
}*/

void display_suffixtree(suffixtree_node *stree,bfslist_suffixtree & bfslist)
{
	
	list<vector<suffixtree_node*> > ::iterator bit;
	vector<suffixtree_node*>:: iterator nit;
	for(bit=bfslist.begin();bit!=bfslist.end();bit++)
	{	for(nit=(*bit).begin();nit!=(*bit).end();nit++)	
		{	
			cout << "  "<< *nit;
			if(*nit!=stree)
			{
			cout << "-----("<< (*nit)->status.string_id << "," << (*nit)->status.leaf_no << ") -----";
				RT=(*nit)->label.rbegin();
				LST=RT->second.rbegin();
				cout << RT->first << "(" << LST->beg_index <<","<<LST->end_index << ")";
				cout <<"------" << (*nit)->slink;
				cout << endl;
			}
		}
	}	
}
	
void preprocess_suffixtree(suffixtree_node *stree,bfslist_suffixtree & bfslist)
{
	suffixtree_node *crnt_node;
	int dfs_count=0,hv,i;
	lca_values=(lca_info*)malloc((suffixtree_node_count+1)*sizeof(lca_info));
	
	list<vector<suffixtree_node*> > ::iterator bit;
	vector<suffixtree_node*>:: iterator nit;
	
	stack<suffixtree_node *> s;
	s.push(stree);
	while(!s.empty())
	{
		crnt_node=s.top();
		//crnt_lnode=new lca_node;
		//crnt_lnode->snode=crnt_snode; // lca node holds suffixtree node address
		crnt_node->num=++dfs_count;  //numbering the node with dfs number
		
		//calculate h(v) of the node
		
		/*hv=1;
		for(int i=1;i<=integer_size;i++)
		{
			if((crnt_node->num & hv)!=0)
			{
				lca_values[crnt_node->num].h=i;
				
				break;
			}
			else hv=hv << 1;
		}*/
		lca_values[crnt_node->num].h= (int)(ceil( log(crnt_node->num&-crnt_node->num) / log(2.0) ) +1);
		s.pop();
		if((crnt_node->status.string_id==0 && crnt_node->status.leaf_no==0) || (crnt_node->status.string_id==-1 && crnt_node->status.leaf_no==-1))
		for(CIT=crnt_node->children.rbegin();CIT!=crnt_node->children.rend();CIT++)
		{
			s.push(CIT->second);
		}
		
	}
	cout << "\n h values\n";
	for(i=1;i<=suffixtree_node_count;i++)
		cout<<lca_values[i].h<<endl;
		
	//exit(1);
	
	//calculate I(v) values by backward traversal of lca tree.
	
	list<vector<suffixtree_node*> >::reverse_iterator BIT;
	vector<suffixtree_node*>::iterator VT;
	int max,maxnum;
	int a;
	short int b,c;
	bool flag;
	
	for(BIT=bfslist.rbegin();BIT!=bfslist.rend();BIT++)
	{
		for(VT=(*BIT).begin();VT!=(*BIT).end();VT++)
		{
			//cout << (*VT)->status.string_id "," <<  (*VT)->status.leaf_no <<"\n";
			//I for internal node.
			
			if(((*VT)->status.string_id==0 && (*VT)->status.leaf_no==0) || ((*VT)->status.string_id==-1 && (*VT)->status.leaf_no==-1))
			{
				/*RT=(*VT)->label.rbegin();
				LST=RT->second.rbegin();
				b=LST->beg_index;
				c=LST->end_index;
				a=RT->first;
			
				cout << *VT << "----"<< a <<"(" << b << "," << c <<")\n";*/
			
				flag=true;
				max=0;
				for(IT=(*VT)->children.begin();IT!=(*VT)->children.end();IT++)
				{
					if(lca_values[(*VT)->num].h <= lca_values[(*IT).second->num].h)
					{
						flag=false;
						break;
					}
					else continue;
				}
				if(flag==true)	lca_values[(*VT)->num].I=(*VT)->num;
				else if(flag==false)
				{
					for(IT=(*VT)->children.begin();IT!=(*VT)->children.end();IT++)
					{
						if(lca_values[lca_values[(*IT).second->num].I].h >=max)
						{
							max=lca_values[lca_values[(*IT).second->num].I].h;
							maxnum=(*IT).second->num;
						}
					}	
					lca_values[(*VT)->num].I=lca_values[maxnum].I;
				}
				
					
				
				
			}
			//I for leaf node.
			else			
				lca_values[(*VT)->num].I=(*VT)->num;
		
		}
	}
	cout << "\n I values\n";
	for(i=1;i<=suffixtree_node_count;i++)
		cout<<lca_values[i].I <<endl;
	
	
	//calculate L(k) values
	for(i=1;i<=suffixtree_node_count;i++)
		lca_values[i].L = null;
	
	for(BIT=bfslist.rbegin();BIT!=bfslist.rend();BIT++)
	{
		for(VT=(*BIT).begin();VT!=(*BIT).end();VT++)
		{
							
			if(*VT==stree || lca_values[(*VT)->num].I != lca_values[(*VT)->parent->num].I)
				lca_values[lca_values[(*VT)->num].I].L = *VT;
			
			else continue;
		}
		
	}
	cout << "\n L values\n";
	for(i=1;i<=suffixtree_node_count;i++)
		cout<<lca_values[i].L <<endl;	
	
	
	//calculate A(v).
	
	list<vector<suffixtree_node*> >::iterator LIT;
	int Abit=1;
	for(LIT=bfslist.begin();LIT!=bfslist.end();LIT++)
	{
		for(VT=(*LIT).begin();VT!=(*LIT).end();VT++)
		{
			Abit= 1 << (lca_values[lca_values[(*VT)->num].I].h-1);
			if((*VT)->status.string_id!=0 && (*VT)->status.leaf_no!=0)
				lca_values[(*VT)->num].A= lca_values[(*VT)->parent->num].A | Abit;
			else 
				lca_values[(*VT)->num].A= 0 | Abit;
		}
	}
	
	
	
	
	cout << "\n A values\n";
	for(i=1;i<=suffixtree_node_count;i++)
		cout<<lca_values[i].A <<endl;
}

suffixtree_node* closest(suffixtree_node *a,int A,int j)
{
	// (a) rightmost 1-bit position in A(x)
	//int l;
	/*l=1;
	while(true)
	{
		if(A & l !=0) break;
		else l= l << 1;
	}*/
	l= (int)(ceil( log(A&-A) / log(2.0) ) +1);
	
	// (b). finding lca
	
	if(l==j) return a;
	else
	{
		k=j-1;
		while(k>0)			//(due)inclde an error condition when no k found
		{
			if((A & (1 << (k-1))) != 0) break;
			else k--;
		}
		Iw= ((~0) << (k -1)) & (lca_values[a->num].I | (1 << (k-1)));
		return(lca_values[Iw].L->parent);
		
	}
	
	
}

suffixtree_node* calculate_lca(suffixtree_node* x,suffixtree_node* y)
{
	int xr,b,comp,j,leftmost1,rightmost1;
	
	/*** 1. CALCULATE lca OF I(x) AND I(y) ****/
		
	xr=lca_values[x->num].I ^ lca_values[y->num].I;
	leftmost1 = xr;
    leftmost1 |= (leftmost1 >> 1);
    leftmost1 |= (leftmost1 >> 2);
    leftmost1 |= (leftmost1 >> 4);
    leftmost1 |= (leftmost1 >> 8);
    leftmost1 |= (leftmost1 >> 16);
    leftmost1 = (leftmost1 & ~(leftmost1>>1));
    leftmost1 = 32 - (int)(ceil( log(leftmost1) / log(2.0) ));
    int frmlsb= (32-leftmost1)+1;
    
	
	b= ((~0) << (8 * sizeof(int)-leftmost1)) & (lca_values[x->num].I | (1 << (frmlsb-1)));//x->num & (1 << (leftmost1-1)); //lca value
	
	/*** 2. calculate j >= h(b) s.t A(x) = A(y)= 1 at j ***/
	
	int Ax= lca_values[x->num].A;
	int Ay= lca_values[y->num].A;
	int andA=Ax & Ay;
	comp=1;j=1;
	//while((j= andA & comp) < lca_values[b].h)
	while(!((j >= lca_values[b].h) && (andA & comp)))
	{
		j++;
		comp=comp << 1;
		
	}
	
	/*** 3 & 4 . THE CLOSESET NODE TO x ON THE SAME RUN AS z ***/
	
	suffixtree_node *closex,*closey;//,*LIw;
			
	closex = closest(x,Ax,j);
	closey = closest(y,Ay,j);
	
	// 5. finfout the lca
	
	if(closex->num < closey->num) return closex;
	else return closey;
}
/*
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
	return 0;
}	*/
