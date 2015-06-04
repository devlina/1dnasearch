namespace hierarchy
{
	multimap<int,set<motif>> from, to;  // the 2 levels of the structure
	
	void init_from()
	{
		match_pattern m1, m2, old;
		int len, i;
		
		while ( true )
		{
			m1 = get_pattern();
			old = m2;
			m2 = get_pattern();
			
			if ( m1.size()==0 )		// even number of motifs
				break;
			if ( m2.size()==0 )		// odd number of motifs
				m2 = old;	// initialized to last even numbered pattern

			reducePattern(m1,m2);
			computeMatrix(m2,m1);
			
			for ( len=0, i=0; i<tree::subSeq.size(); ++i )
				len += (*(tree::subSeq.begin()+i)).size();
				
			from.insert(make_pair(len,tree::subSeq));
		}
	}

	int next_level()
	{
		if ( to.size()==1 )
			return 1;
		from = to;
		to.clear();	// clear the higher level
		

		if ( from.size()%2 == 1 )	// odd
			to.insert(
}
