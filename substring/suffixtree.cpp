#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <utility>

using namespace std;

typedef struct{
	short int beg_index,end_index;
}index_range;

typedef list<index_range> index_list;

/*typedef struct{
        int pattern_num;
        short int start_pos;
        }pattern_pos_pair;
*/
class suffixtree_node{
      public :
             bool visit;
             multimap<int,int> status;
             suffixtree_node *slink,*parent;
             multimap<int,index_list> label;
             map<int,suffixtree_node*> children;
             };
#include "settings2.h"
//int max_index;
//suffixtree_node *root,*intern,*leaf,*activenode,*prev,*temp;  

void update_suffixlink(suffixtree_node *prev)
{
     LT=prev->label.find(pattern_prev);
	LST=LT->second.rbegin();
     (LST->beg_index == LST->end_index) ? prev->slink=root : prev->slink=activenode;
}

void set_index_when_root(int j,int i)
{
	startmatch=j;
	endmatch=i;
	done=false;
	if(startmatch==endmatch)
     	{
        	done=true;
                prev=activenode;
                if(prev!=root) update_suffixlink(prev);                             
                        
     	}
     	IT=temp->children.find(current_pattern[j]);
     	
     	if(IT==temp->children.end())
     	{		leaf=new suffixtree_node;
                cur.beg_index=i;
		cur.end_index=max_index;
                crnt.clear();
                crnt.push_back(cur);
		leaf->visit=false;
		leaf->status.insert(make_pair(pattern_crnt+1,j+1));		leaf->slink=null;
		leaf->label.insert(make_pair(pattern_crnt,crnt));
		temp->children.insert(make_pair(current_pattern[i],leaf));
		leaf->parent=temp;
		activenode=temp;
		now=j;
                                                                   
     	}
}

void set_index_when_nonroot()
{	
	if(temp->slink!=null) temp=temp->slink;
     	RT=activenode->label.rbegin();
	LST=RT->second.rbegin();
     	startmatch=LST->beg_index;
     	endmatch=LST->end_index;
     	if(endmatch==max_index) endmatch=e;
     	done=false;
       
}



void adjust_suffixtree(vector<vector<int> >& pattern,int i,int j)
{
    //suffixtree_node *intern; 
	
	while(!done)
    	{		old_startmatch=startmatch;
                IT=temp->children.find(current_pattern[startmatch]);
                tmp=IT->second;
                RT=tmp->label.rbegin();
		LST=RT->second.rbegin();
                beg=old_beg=LST->beg_index;
                end=LST->end_index;
                if(end==max_index) end=e;
                startmatch++; beg++;
                //modified
                while(beg <= end && startmatch < endmatch)
                {
                	if(pattern[pattern_prev][beg] == current_pattern[startmatch])
                        {
				beg++; startmatch++;
                        }
                        else break;
                }
                if(beg > end && startmatch <= endmatch)
                {
                       temp=IT->second;
                       done=false;
                }
                else if(beg <= end && startmatch >= endmatch)
                {
			if(startmatch > endmatch)
			
			 startmatch=i;
                        if(pattern[pattern_prev][beg] != current_pattern[startmatch])
                        {
				suffixtree_node *intern; 					 intern= new suffixtree_node;
                                cur.beg_index=old_beg;
				cur.end_index=beg-1;
                                crnt.clear();
                                crnt.push_back(cur);
                                intern->visit=false;
                                intern->status.insert(make_pair(-1,-1));
                                intern->slink=null;
                                intern->label.insert(make_pair(pattern_crnt,crnt));
                                if(startmatch!=i)
                                {
                                	cur.beg_index=old_startmatch;
					cur.end_index=startmatch-1;
                                        crnt.clear();
                                        crnt.push_back(cur);
                                        intern->label.insert(make_pair(pattern_crnt,crnt));
                                }
                                temp->children.erase(IT->first);
                                temp->children.insert(make_pair(current_pattern[old_startmatch],intern));
                                prev=activenode;
                                activenode=intern;
                                intern->parent=temp;
                                LST->beg_index=beg;
                                tmp->parent=intern;
				intern->children.insert(make_pair(pattern[pattern_prev][beg],tmp));
				if(prev!=root) update_suffixlink(prev);				leaf=new suffixtree_node;
				cur.beg_index=i;
				cur.end_index=max_index;
				crnt.clear();
				crnt.push_back(cur);
				leaf->visit=false;
				leaf->slink=null;
				leaf->label.insert(make_pair(pattern_crnt,crnt));
				intern->children.insert(make_pair(current_pattern[i],leaf));				leaf->parent=intern;
				leaf->status.insert(make_pair(pattern_crnt+1,j+1));
				now=j;
				done=true;
			}
			else{
				done=true;
				phase=true;
			}
		}
                else if(beg > end && startmatch > endmatch)
	        {
			leaf=new suffixtree_node;
			leaf->visit=false;
			leaf->status.insert(make_pair(pattern_crnt+1,j+1));
			cur.beg_index=i;
			cur.end_index=max_index;
			crnt.clear();
			crnt.push_back(cur);
			leaf->label.insert(make_pair(pattern_crnt,crnt));
			temp->children.insert(make_pair(current_pattern[i],leaf));
			leaf->parent=temp;
			leaf->slink=null;
			now=j;
			done=false;                                
		}
		else if(beg <= end && startmatch > endmatch)
		{
			startmatch = endmatch =i;
			done=false;
		}
                               
             
	} 
}   
suffixtree_node* create_stree(int num,vector<vector<int> >& pattern)
{
                 
                 
	root=new suffixtree_node;
	root->status.insert(make_pair(0,0));
	root->slink=null;
                 /*int now=0,e;
                 index_range cur;
                 index_list crnt;  */
                 //map<int,suffixtree_node*>::iterator IT;  
                 
	for(int p=0;p<pattern.size();p++)
	{
	//int pattern_crnt,pattern_prev;  //holds the previous and current pattern index
		if(p==0)
		{     
				pattern_crnt=pattern_prev=p;
		}						       												                                                        
		else {pattern_crnt=p;pattern_prev=p-1;}
		activenode=root;
		vector<int> :: iterator vt;
		vt=current_pattern.begin();
		current_pattern.insert(vt,pattern[pattern_crnt].begin(),pattern[pattern_crnt].end());
		vt=previous_pattern.begin();
		previous_pattern.insert(vt,pattern[pattern_prev].begin(),pattern[pattern_prev].end());
                      
		now=-1;
		max_index=current_pattern.size()-1;
		for(int i=0;i<current_pattern.size();i++)
		{
			e=i;
			phase=false;
			for(int j=now+1;j<=i && phase==false;j++)
			{
				(activenode==root)? temp=root : temp=activenode->parent;
				if(temp==root || temp->slink==null) set_index_when_root(j,i);
				else if(temp->slink!=null) set_index_when_nonroot();
				adjust_suffixtree(pattern,i,j);       
                                                                
			}
		}
                      
	}
	return (root);
}

void dfs(suffixtree_node *ptr)
{
	ptr->visit=true;
	int n,m,p;
	suffixtree_node *ptr1;
//	void dftraverse(ptr);
	for(IT=ptr->children.begin();IT!=ptr->children.end();IT++)
	{
		n=IT->first;
		cout << n << "," ;
		multimap<int,int>::iterator ST;
		ptr=IT->second;
		for(ST=ptr->status.begin();ST!=ptr->status.end();ST++)
		{
 			m=ST->first;p=ST->second;
 			cout << "("<< m <<"," << p << ")  ";
		}
		cout <<endl;
		//ptr=IT->second;
		if(ptr->visit==false)
			dfs(ptr);
	}


}


int main()
{
	int str[6]={1,2,3,1,2,-1};
	vector<vector<int> > pattern;
	vector<int> vec;
	suffixtree_node *sft;
	int num=1;
	for(int i=1;i<=6;i++) vec.push_back(str[i-1]);
	pattern.push_back(vec);
	sft=create_stree(num,pattern);
	//dfs(sft);
	return 0;
}
             
