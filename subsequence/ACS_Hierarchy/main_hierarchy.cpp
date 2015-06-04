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
#include "hierarchy.h"

int main ( int argc, char* argv[] )
{
	cout<<"Critical Length : ";
	cin>>tree::cLen;
	
	devlina_main();
	cout<<"\ndevlina_main() executed properly\n";
	
	hierarchy::init_from();
	cout<<"\nhierarchy::init_from() executed properly\n";

	int i;
	set<motif> output;

/*	i=0;
	output = (hierarchy::from.begin())->second;
	for ( set<motif>::iterator si=output.begin(); si!=output.end(); ++si )
	{
		cout<<"Motif "<<++i<<" : \n";
		output_motif(*si);
		cout<<endl;
	} */
		
	while ( hierarchy::next_level() > 1 );

	cout<<"\n\nList of all substrings : ";
	i=0;
	output = (hierarchy::to.begin())->second;
	for ( set<motif>::iterator si=output.begin(); si!=output.end(); ++si )
	{
		cout<<"\n"<<"Motif "<<++i<<" :"<<endl;
		output_motif(*si);
	}
	
	fflush(stdin);
	getchar();
	return 0;
}
