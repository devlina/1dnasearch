#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <utility>
#include <queue>
#include <algorithm>

using namespace std;
#include "settings_substring.h"

children_key tmpkey;

// set the suffixlink pointer
void update_suffixlink(suffixtree_node *prev) 
{
    RT=prev->label.rbegin();
	LST=RT->second.rbegin();
	/*if edge contains a single character x then point to root 
	otherwise if contais xa point to node with edge label a*/
    (LST->beg_index == LST->end_index) ? prev->slink=root : 
    					prev->slink=activenode;
}

//this function creates a new leaf node and add it to the tree
void add_leaf(vector<vector<int> >& combined_pattern,int i,int j,
			suffixtree_node *father)
{
	leaf=new suffixtree_node;
	suffixtree_node_count++;
	cur.beg_index=i;
	cur.end_index=max_index;	crnt.clear();
	crnt.push_back(cur);
	//leaf->status.insert(make_pair(pattern_crnt+1,j+1));
	leaf->status.string_id=pattern_crnt+1;
	leaf->status.leaf_no=j+1;	leaf->label.insert(make_pair(pattern_crnt,crnt));
	leaf->slink=null;
	leaf->parent=father;
	ckey.time= suffixtree_node_count;
	ckey.value=combined_pattern[pattern_crnt][i];
	father->children.insert(make_pair(ckey,leaf));
	prev=activenode;
	activenode=father;
	if(prev!=root || prev->slink == null)
		update_suffixlink(prev);
	now=j;
}


// set the path indices when traversal starts from the root

void set_index_when_root(int i,int j)
{
	/*get the begining and end indices of pattern to be serached
	from merged_pattern */
	startmatch=j;
	endmatch=i;
	done=false;
	case_nonroot=false;
	/*if(startmatch==endmatch)
     	{
     		IT=temp->children.find(pattern[pattern_crnt][j]);
     	
     		if(IT==temp->children.end())
     		{		
			add_leaf(pattern,i,j,temp);
			done=true;
                                                                   
     		}
     	}*/
}

//set the path indices when traversing from some internal node 
void set_index_when_nonroot()
{	
	if(temp->slink!=null) temp=temp->slink;
    RT=activenode->label.rbegin();
    crnt_index=RT->first;
	LST=RT->second.rbegin();
	//get the begining and end indices of internal node's edge
    startmatch=LST->beg_index;
    endmatch=LST->end_index;
    case_nonroot=true;
    if(endmatch==max_index && RT->first==pattern_crnt) endmatch=e;
    done=false;
     
}


/*class check_presence{
	int C;
public :
	explicit check_presence(int val) : C(val) { }
	bool operator()(const pair<children_key,suffixtree_node*>& c1)
	{
		return c1.first.value==C;
	}
};*/

/* search suffix tree for the current character and insert it 
properly if it is not present.*/
void adjust_suffixtree(vector<vector<int> >& combined_pattern,
						int i,int j)
{
    //suffixtree_node *intern; 
	
	while(!done)
    {		old_startmatch=startmatch;
		if(case_nonroot!=true) crnt_index=pattern_crnt;
		
		//ckey.string_id=crnt_index;
		//ckey.position=startmatch;
		//ckey.value=pattern[crnt_index][startmatch];
        //IT=temp->children.find(pattern[crnt_index][startmatch]);
        //IT=temp->children.find(ckey);
        
        //find the node started with the desired character.
		IT=find_if(temp->children.begin(),temp->children.end(),
			check_presence(combined_pattern[crnt_index][startmatch]));
		
		//If node not found add a new child leaf node		
		if(IT==temp->children.end())
		{
			add_leaf(combined_pattern,i,j,temp);
			done=true; 
			continue;
		}
		//store the node information from which traversal starts
		tmpkey=IT->first;
		tmp=IT->second;
		RT=tmp->label.rbegin();
		//int c=RT->first;
		LST=RT->second.rbegin();
		//get the beining and end indices of current node's egde label
		beg=old_beg=LST->beg_index;
		end=LST->end_index;
		if(end==max_index && RT->first== pattern_crnt) end=e;
		startmatch++; beg++;
          
		/*start matching of strings hold by (start_match,end_match)
		and (beg,end)*/
		while(beg <= end && startmatch < endmatch )
		{	
            /* if checking for active node then check with the label 
            of active node stored in crnt_index.*/    	
			if(case_nonroot==true) 
			{
		   		if(combined_pattern[RT->first][beg] == 
		   		combined_pattern[crnt_index][startmatch])        
		   		{
					beg++; startmatch++;
                }
                else break;
			}
			/* otherwise if checking for root then check with the 
			label of curren pattern stored in pattern_crnt.*/
           	else if(combined_pattern[RT->first][beg] == 
           			combined_pattern[pattern_crnt][startmatch])
			{	
				beg++; startmatch++;
			}
			else break;
		}
                
		/*if the label of current node ends but the matching pattern 
		does not then go down by 1 level.*/
		if(beg > end && startmatch <= endmatch)
		{
			temp=IT->second;
			done=false;
		}
		
		/*if the matching string comes to its end(root case) or 
		exhausts(non root case) then check for the presence of 
		desired character and if not present then add it to the tree*/
		else if(beg <= end && 
				((startmatch <= endmatch && case_nonroot==false)
				 || (startmatch > endmatch && case_nonroot==true)))
		{
			/*get the character(i'th) to be added if traversal have 
			been started from non-root node*/
			if(startmatch > endmatch && case_nonroot==true)
				startmatch=i;
			 	
			//add the character
			if(combined_pattern[RT->first][beg] != 
				combined_pattern[pattern_crnt][startmatch])
			{
				//create internal node and add it to the tree
				suffixtree_node *intern; 		
				intern= new suffixtree_node;
				suffixtree_node_count++;
				cur.beg_index=old_beg;
				cur.end_index=beg-1;
				crnt.clear();
				crnt.push_back(cur);
				intern->status.string_id=-1;
				intern->status.leaf_no=-1;
				//intern->slink=null;
				intern->label.insert(make_pair(RT->first,crnt));
				temp->children.erase(IT->first);
				
				//ckey.string_id=RT->first; //pattern_crnt;
				//ckey.position=old_beg;//old_startmatch;
				//ckey.value=pattern[pattern_crnt][old_startmatch];
				ckey.time=tmpkey.time;//suffixtree_node_count;
				ckey.value=combined_pattern[RT->first][old_beg];
				temp->children.insert(make_pair(ckey,intern));
				/*ckey.string_id=pattern_crnt;
				ckey.position=old_startmatch;
                temp->children.insert(make_pair(ckey,intern));*/
				intern->parent=temp;
				LST->beg_index=beg;
				tmp->parent=intern;
				
				//ckey.string_id=pattern_prev;
				//ckey.position=beg;
				ckey.time=suffixtree_node_count;//tmpkey.time;
				ckey.value=combined_pattern[pattern_prev][beg];
				intern->children.insert(make_pair(ckey,tmp));
				//add new character at a new leaf node
				add_leaf(combined_pattern,i,j,intern);
				done=true;
			}
			else{
				done=true;
				phase=true;
			}
		}
		
		/*IF THE LABEL OF CURRENT NODE AND MATCHING STRING BOTH 
		EXHAUSTS ADD THE DESIRED CHARACTER IN THE TREE IF IT IS 
		NOT PRESENT*/
		else if(beg > end && startmatch > endmatch )		{
			if(case_nonroot==false){
				done=true;
				phase=true;
			}
			else if(startmatch > endmatch && case_nonroot==true)
			{ 	
			 	startmatch=i;
			
			temp=IT->second;
			
			//ckey.string_id=pattern_crnt;
            //ckey.position=startmatch;
            //ckey.value=pattern[pattern_crnt][startmatch];
            
            IT=find_if(temp->children.begin(),temp->children.end(),
            	check_presence(
            	combined_pattern[pattern_crnt][startmatch]));             
               // IT=temp->children.find(ckey);
			
			if(IT==temp->children.end())
			{
				add_leaf(combined_pattern,i,j,temp);
				done=true; 
			}
			//extensions and phase both completed
			else
			{
				done=true;
				phase=true;
			}   
			}                            
		}
		
		/*IF MATCHING STRING EXHAUSTS WHILE LABEL OF CURRENT NODE 
		DOES NOT THEN DESIRED CHARACTER IS ALREADY THERE SO NOTHING 
		TO BE DONE,HENCE PHASE HAS BEEN COMPLETED.*/
		else if(beg <= end && startmatch > endmatch)
		{
			done=true;
			phase=true;
		}
    }
}            
	
//function to build the suffix tree.  
suffixtree_node* create_stree(vector<vector<int> >& combined_pattern)
{
                        
	//create root
	root=new suffixtree_node;
	//root->status.insert(make_pair(0,0));
	root->status.string_id=0;
	root->status.leaf_no=0;
	root->slink=root;
	/*int now=0,e;
	index_range cur;
	index_list crnt;  */
	//map<int,suffixtree_node*>::iterator IT;  
        
	suffixtree_node_count=1; //initialize node count 
	
	/*start building suffixtree for each pattern in combined_pattern
	get one pattern (until all pattern has been added)at a time and 
	add it to the tree       */
	for(int p=0;p<combined_pattern.size();p++)
	{
	  //holds the previous and current pattern index
		if(p==0)	pattern_crnt=pattern_prev=p;
													                                                        
		else {pattern_crnt=p;pattern_prev=p-1;}
		activenode=root;
		/*current_pattern.clear();
		previous_pattern.clear();
		vector<int> :: iterator vt;
		vt=current_pattern.begin();
		current_pattern.insert(vt,pattern[pattern_crnt].begin(),
		pattern[pattern_crnt].end());
		vt=previous_pattern.begin();
		previous_pattern.insert(vt,pattern[pattern_prev].begin(),
		pattern[pattern_prev].end());*/
                      
		now=-1;
		//get the index of last character in combined_pattern
		max_index=combined_pattern[pattern_crnt].size()-1;
		
		//start a phase
		for(int i=0;i<combined_pattern[pattern_crnt].size();i++)
		{
			e=i;
			phase=false;
			
			//start an extension
			for(int j=now+1;j<=i && phase==false;j++)
			{
				(activenode==root)? temp=root : 
									temp=activenode->parent;
				if(temp==root || temp->slink==null) 
					set_index_when_root(i,j);
				else if(temp->slink!=null) 
					set_index_when_nonroot();
				adjust_suffixtree(combined_pattern,i,j); 
				                      
			}
		}
                      
	}
	return (root);
}


/*function to create list of nodes at each level by making a 
breadth first traversal of the suffix tree*/
void bfs(suffixtree_node *ptr,bfslist_suffixtree & bfslist)
{
	/*a node starting from leaf is inserted into the queue when 
	visited.then the node is removed and inserted into the list
	and all its child are added in the queue.Once a node is removed
	all the child at same level are inserted in the list.process
	continues until the queue gets empty*/
	queue<suffixtree_node *> q;
	int n,m,p;
	suffixtree_node *crnt_child;
	vector<suffixtree_node *> current_level_nodes;

	q.push(ptr);
	q.push(null);
	current_level_nodes.push_back(ptr);
	bfslist.push_back(current_level_nodes);
	current_level_nodes.clear();
	while(!q.empty())
	{
		
		crnt_child=q.front();
		q.pop();
		if(crnt_child==null && !q.empty())
		{
			q.push(null);
			bfslist.push_back(current_level_nodes);
			current_level_nodes.clear();	
		}
		else if(!q.empty())
		{
			cout <<"\n"<< crnt_child;
			if(crnt_child !=ptr)
			{
				/*ST=crnt_child->status.begin();
				//cout << "-----("<< ST->first << "," << 
				ST->second << ") -----";*/
				cout << "-----("<< crnt_child->status.string_id << 
					"," << crnt_child->status.leaf_no << ") -----";
				RT=crnt_child->label.rbegin();
				LST=RT->second.rbegin();
				cout << RT->first << "(" << LST->beg_index <<","<<
				LST->end_index << ")";
				cout <<"------" << crnt_child->slink;
			}
		
			for(IT=crnt_child->children.begin();
				IT!=crnt_child->children.end();IT++)
			{
				q.push(IT->second);
				current_level_nodes.push_back(IT->second);
	
			}
		}
		
	}
	cout << endl;
	list<vector<suffixtree_node*> > ::iterator bit;
	/*vector<suffixtree_node*>:: iterator nit;*/
	
	//display the node list
	for(bit=bfslist.begin();bit!=bfslist.end();bit++)
	{	for(VT=(*bit).begin();VT!=(*bit).end();VT++)		
			cout << "  "<< *VT;
		
		cout << endl;
	}		

}


