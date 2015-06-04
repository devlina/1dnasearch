#include <string>
#include <map>
#include <set>

#include "tree.h"

void reducePattern(motif &s1, motif &s2)
{
	int i;
	
	if (s1.size() > s2.size())
		s1.swap(s2);
	// s2 is always greater than s1.

	map<int,bool> s2Map;
	
	for( i=0; i<(int)s2.size(); ++i )
		s2Map[s2[i]] = false;
	// insertion in the map complete.

	for( i=0; i<(int)s1.size(); ++i )
	{
		map<int,bool>::iterator iter = s2Map.find(s1[i]);
		if(iter == s2Map.end() )
		{
			s1.erase(s1.begin()+i);
			--i;
		}
		else
			s2Map[s1.at(i)] = true;
	}
	// The motif s1 is reduced. Now reducing s2.

	for( i=0; i<(int)s2.size(); i++)
		if(s2Map[s2[i]] == false)
		{
			s2.erase(s2.begin()+i);
			--i;
		}
}

void computeMatrix(const motif &s1, const motif &s2)
{
	int i, j;
	int c[s1.size()+1][s2.size()+1];
	
	map<int,tree::node*> validJump;
	// stores all the valid jump points, first int has the 2 indices, i and j, side by side
	// i.e i<<16 + j. The node* is the pointer to corresponding location of the mem
	// Initially all the node* are NULL

    // tree::subSeq.clear();
    // clear the tree::subSeq that holds old data
    
	multimap<short,short> jumpSetRow;
	// set of jumps sorted by rows

	multimap<short,short> jumpSetClm;
	// set of jumps sorted by clms

	// Matrix computation part
	{
		for(i=0;i<=(int)s1.size();i++)
			c[i][0] = 0;    // initialise first column with all 0s
		
		for(j=0;j<=(int)s2.size();j++)
			c[0][j] = 0;    // initialise first row with all 0s

		for(i=1;i<=(int)s1.size();i++)
		{
			for(j=1;j<=(int)s2.size();j++)
			{
				if(s1.at(i-1) == s2.at(j-1))    // match found
				{
					c[i][j]= c[i-1][j-1] + 1;   // diagonal+1

					jumpSetRow.insert(pair<short,short>(i,j));
					jumpSetClm.insert(pair<short,short>(j,i));

					tree::node *tmp = new tree::node();
					tmp->i = i;
					tmp->j = j;
					tmp->matNo = c[i][j];
					tmp->ch = s1.at(i-1);
					if ( c[i][j]==1 )
					{
						motif m;
						m.push_back(tmp->ch);
						tmp->sub.insert(m);
					}

					int key = (((int)i)<<16) + j;
					validJump[key] = tmp;

					multimap<short,short>::iterator ub, lb, it;
					
					for ( int p=j-1, limit=0; p>0; --p )	// for each column
					{
						ub = jumpSetClm.upper_bound((short)(p));
						lb = jumpSetClm.lower_bound((short)(p));
						
						for ( it=lb; it!=ub; ++it )
							if ( it->second < i && it->second >= limit )
							{
								limit = it->second;
								int key = (((int)it->second)<<16) + ((int)it->first);
								if ( validJump[key]->matNo < tmp->matNo )	// redundant check??
									tmp->link.insert(validJump[key]);
							}
					}
					
					/*
					// clm jumps added to link set [?][j-1]
					{
						ub = jumpSetClm.upper_bound((short)(j-1));
						lb = jumpSetClm.lower_bound((short)(1));
							// jumpSetClm.lower_bound((short)(j-1));
						for ( it=lb; it!=ub; ++it )
						{
							if ( it->second < i )
							// to eliminate the [i][j-1] valid jump case
							{
								int key = (((int)it->second)<<16) + ((int)it->first);	// j-1;
								if ( validJump[key]->matNo <= tmp->matNo-1 )
									tmp->link.insert(validJump[key]);
							}
						}
					}

					// row jumps added to link set ... [i-1][?]
					{
						ub = jumpSetRow.upper_bound((short)(i-1));
						lb = jumpSetRow.lower_bound((short)(1));
							// jumpSetRow.lower_bound((short)(i-1));
						for ( it=lb; it!=ub; ++it )
						{
							if ( ((int)it->second) < j )
							{
								int key = (((int)it->first)<<16) + ((int)it->second);	// (((int)(i-1))<<16) + it->second;
								if ( validJump[key]->matNo <= tmp->matNo-1 )
									tmp->link.insert(validJump[key]);
							}
						}
					}

					// diagonal jump
					{
						if ( c[i][j]>1 && s1.at(i-2)==s2.at(j-2) )
							// c[i][j] has to be greater than 1, else this jump is non-existant,
							// besides we also eliminate the out-of-range problem !!
						{
							int key = (((int)(i-1))<<16) + j-1;
							tmp->link.insert(validJump[key]);
						}
					} */

					tree::addInfoChild(tmp);
				}
				else
					c[i][j] = c[i][j-1] > c[i-1][j] ? c[i][j-1] : c[i-1][j];
			}
		}
		// MATRIX generation complete.
		
		// Matrix printing
/*		{
			//cout<<"\n|:"<<s1<<"\t"<<"-:"<<s2;
			for(i=0;i<=(int)s1.size();i++)
			{
				cout<<endl;
				for(j=0;j<=(int) s2.size();j++)
					cout<<c[i][j]<<"  ";
			}
		} */
	}

	// list of valid jumps
/*	{
		cout<<"\n\nList of valid jumps:";
		map<int,tree::node*>::iterator iter;
		for ( iter=validJump.begin(); iter!=validJump.end(); ++iter )
		{
			int x, y;
			y = (iter->first)>>16;
			x = (iter->first) & 0x0000FFFF;
			cout<<"\ni:"<<y<<"\t j:"<<x;	//<<"\t Add:"<<iter->second;
		}
		//map<int,tree::node*> validJump;
	}	*/

	for(i=1;i<=(int)s1.size();i++)
	{
		if ( s1.at(i-1)==s2.at((int)s2.size()-1) )
		{
			int key = (((int)i)<<16) + (int)s2.size();
			if ( validJump[key]->matNo>=tree::cLen )
				tree::loadSub(validJump[key]);
		}
	}
	
	for(j=1;j<=(int)s2.size();j++)
	{
		if ( s2.at(j-1)==s1.at((int)s1.size()-1) )
		{
			int key = (((int)s1.size())<<16) + j;
			if ( validJump[key]->matNo>=tree::cLen )
				tree::loadSub(validJump[key]);
		}
	}

	// free the dynamically allocated nodes of the tree
	for ( map<int,tree::node*>::iterator i=validJump.begin(); i!=validJump.end(); ++i )
	    delete  (*i).second;
}
