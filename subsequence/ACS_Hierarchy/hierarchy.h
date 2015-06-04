#include "generate.h"

namespace hierarchy
{
	multimap<int,set_motif> from, to;  // the 2 levels of the structure
	
	void init_from()	// initialize the first level
	{
		pattern m1, m2, old;
		
		while ( true )
		{
			bool m1_ok = get_matched_motif(m1);	// m1 = get_pattern();
			old = m2;
			bool m2_ok = get_matched_motif(m2);	// m2 = get_pattern();
			
			if ( m1_ok==false || m1.size()==0 )		// even number of motifs
				break;
			if ( m2_ok==false || m2.size()==0 )		// odd number of motifs
			    m2 = old;   // initialized to last even numbered pattern

			output_motif(m1);	puts("");
			output_motif(m2);	puts("*****");
			
			tree::subSeq.clear();
			
			reducePattern(m1,m2);
			computeMatrix(m2,m1);
			cout<<"subSeq.size() = "<<tree::subSeq.size()<<endl<<endl;
			
			int len=0;
			for ( set_motif::iterator iter=tree::subSeq.begin(); iter!=tree::subSeq.end(); ++iter )
			{
				motif tmp = *iter;
				len = len + tmp.size();
			}
				
			from.insert(make_pair(len,tree::subSeq));
		}
	}
	
	int next_level()	// compute the next level
	{
		if ( from.size()==1 )
		    return 1;

		printf("%d\n",from.size());
		to.clear();	// clear the higher level
		
		int i=1;
		multimap<int,set_motif>::iterator iter1;	// points to elements in ascending order
		multimap<int,set_motif>::reverse_iterator iter2;	// points to elements in descending order
		for ( iter1=from.begin(), iter2=from.rbegin(); i<=(from.size()+1)/2; ++iter1, ++iter2, ++i )
		{
			if ( i==(from.size()+1)/2 && from.size()%2==1 )	// reached the single middle element
			{
				// automatic promotion to next level, without any computation
				to.insert(*iter1);
				continue;
			}
			
			tree::subSeq.clear();	// clear the old subsequences, not cleared by default
			set<motif> set1=iter1->second;
			set<motif> set2=iter2->second;
			for ( set<motif>::iterator st1_iter=set1.begin(); st1_iter!=set1.end(); st1_iter++ )
				for ( set<motif>::iterator st2_iter=set2.begin(); st2_iter!=set2.end(); st2_iter++ )
				{
					motif tmp1=*st1_iter;
					motif tmp2=*st2_iter;
					
					// cout<<endl;	output_motif(tmp1);	cout<<"\t";	output_motif(tmp2);
					
					reducePattern(tmp1,tmp2);
					computeMatrix(tmp2,tmp1);
				}

			// erase those subsequences with length less than the critical length
			for ( set_motif::iterator iter=tree::subSeq.begin(); iter!=tree::subSeq.end(); ++iter )
				if ( (*iter).size() < tree::cLen )
					tree::subSeq.erase(iter);

			int len=0;
			for ( set_motif::iterator iter=tree::subSeq.begin(); iter!=tree::subSeq.end(); ++iter )
			{
				motif tmp = *iter;
				len = len + tmp.size();
			}
				
			to.insert(make_pair(len,tree::subSeq));
		}
		
		from = to;		
		return to.size();
	}
}
