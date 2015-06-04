int input_motif ( motif &s )
{
	int i=0, elm;
	do
	{
		cout<<++i<<" : ";
		cin>>elm;
		if ( elm )
			s.push_back(elm);
	} while ( elm );

	return i;
}

int output_motif ( const motif &s )
{
	int i;
	for ( i=0; i<s.size(); ++i )
		cout<<i+1<<" : "<<s[i]<<endl;

	return i;
}
