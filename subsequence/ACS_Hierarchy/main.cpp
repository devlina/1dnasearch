#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

#include "settings.h"
#include "io_dna.h"
#include "acs.h"

int main ( int argc, char* argv[] )
{
	cout<<"Critical Length : ";
	cin>>tree::cLen;
	
	motif s1, s2;
	cout<<"Input Motif 1"<<endl;
	input_motif(s1);
	cout<<"Input Motif 2"<<endl;
	input_motif(s2);

	reducePattern(s1,s2);

	cout<<"Motif 1"<<endl;
	output_motif(s1);
	cout<<"Motif 2"<<endl;
	output_motif(s2);

//	s1 = "MZJAWXU";		s2 = "XMJYAUZ";
//	s1 = "AXBYAZBMNO";	s2 = "BMANBOAXYZ";

	tree::subSeq.clear();
	computeMatrix(s2,s1);

	cout<<"\n\nList of all substrings : ";
	int i=0;
	for ( set<motif>::iterator si=tree::subSeq.begin(); si!=tree::subSeq.end(); ++si )
	{
		cout<<"\n"<<"Motif "<<++i<<" :"<<endl;
		output_motif(*si);
	}
	
	fflush(stdin);
	getchar();
	return 0;
}
