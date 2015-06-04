#define null 0

int integer_size=8*sizeof(int);
/****************************************************************/
//definition of suffix tree components

//edge label defintion of a node		
typedef struct{
	short int beg_index,end_index;
}index_range;

/*leaf node information contains, string to which it belongs and
number of leaf*/
typedef struct{
	short int string_id,leaf_no;
}leaf_identifier;

//list for storing labels
typedef list<index_range> index_list;

class suffixtree_node;

//key structure of children map
typedef struct{
	//int string_id,position,value;
	int time,value;
}children_key;

/*class compare_children{
public:
	int operator()(const children_key &a,const children_key &b)
	{
		if(a.string_id < b.string_id)
			return 1;
		else if(a.string_id == b.string_id)
			return a.position < b.position;
	}
};*/

//function object to compare two child nodes.
class compare_children{
public:
	int operator()(const children_key &a,const children_key &b)
	{
		return(a.time < b.time);
	}
};

//SUFFIXTREE NODE DEFINITION

class suffixtree_node{
      public :
             int num;
             leaf_identifier status;
             suffixtree_node *slink,*parent;
             multimap<int,index_list> label;
             //map<int,children_value,compare_children> children;
             map<children_key,suffixtree_node*,compare_children> children;
             };
             

/*function object to check whether a child starting from a certain
character is present or not*/

class check_presence{
	int C;
public :
	explicit check_presence(int val) : C(val) { }
	bool operator()(const pair<children_key,suffixtree_node*>& c1)
	{
		return c1.first.value==C;
	}
};
/**************************************************************/
		// LCA NODE DEFINITION

/*class lca_node : public suffixtree_node{
public:
	int num;
	int h;
	int I;
	int A;
	int L;
	};*/
/*****************************************************************/ 

suffixtree_node *root,*intern,*leaf,*activenode,*prev,*temp,*tmp;

 
map<children_key,suffixtree_node*>::iterator IT; // children iterator
// children reverse iterator
map<children_key,suffixtree_node*>::reverse_iterator CIT;
// label reverse iterator 
multimap<int,index_list>::reverse_iterator RT; 
multimap<int,index_list>::iterator LT;  //label iterator
list<index_range>::reverse_iterator LST; // list reverse iterator
//multimap<int,int>::iterator ST;		//status iterator

// list of node as appeared in bfs traversal of suffix tree
typedef list<vector<suffixtree_node*> > bfslist_suffixtree; 
list<vector<suffixtree_node*> >::reverse_iterator BIT;
vector<suffixtree_node*>::iterator VT;
 
int  now,e,startmatch,old_startmatch,endmatch,pattern_crnt;
int suffixtree_node_count,pattern_prev,crnt_index,max_index;
 
 short int beg,old_beg,end;
 index_range cur;
 index_list crnt; 
 children_key ckey; 
 bool phase,done,case_nonroot;
 
 vector<int> current_pattern,previous_pattern;
