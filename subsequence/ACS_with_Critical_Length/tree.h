#include <algorithm>
#include <set>

namespace tree
{
	class node
	{
	public:
		short i, j;	// short = 16 bits, range=30K+
		int ch;		// the element which caused the valid jump
		set<node*> link;	// links to all children
		set<motif> sub;     // set of all subsequences beginning from this node
		int matNo;  // the number of the cell in the LCS matrix
	};
	
	int cLen;	// the critical length. All subsequences must be >= cLen
	set<motif> subSeq;	// all the subsequences, (all with ch as initial character)

	void addInfoChild ( node* p )
	{
		set<node*>::iterator ni, nj;
		set<motif>::iterator si;
		for ( ni=p->link.begin(); ni!=p->link.end(); ++ni )
		{
			// *ni points to the link
			for ( si=(*ni)->sub.begin(); si!=(*ni)->sub.end(); ++si )
			{
				motif tmp(*si);
				tmp.push_back(p->ch);
				p->sub.insert(tmp);
			}
		}

		return;
	}

	void allCombinations ( int n, int k, motif str )
	// computes all compinations of nCk and prints
	// those characters of str.
	{
		if ( k>n )  // invalid case
			return;
		else
		{
			int c[MaxSubSeqLength], i, j;
			motif s;
			
			c[0] = -1;
			for ( i=1; i<=k; ++i )
				c[i] = i;

			j=1;
			while ( j!=0 )
			{
				s.clear();
				for ( i=1; i<=k; ++i )
					s.push_back(str.at(c[i]-1));
				tree::subSeq.insert(s);
				
				j=k;
				while ( c[j]==(n-k+j) )
					--j;
				    
				c[j]++;
				
				for ( i=j+1; i<=k; ++i )
					c[i]=c[i-1]+1;
			}
		}
	}

	void loadSub ( node *p )
	{
		set<motif>::iterator si;
		for ( si=p->sub.begin(); si!=p->sub.end(); ++si )
			subSeq.insert(*si);
	}
}
