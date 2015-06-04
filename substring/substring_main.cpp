#include "_generate.h"
#include "common_substring.h"

int main(void)
{
	int i;
	cout << "Enter critical length : ";
	cin >> clen;
	
	lexer_main();//generate squence of motifs found in DNA patterns
	
	//vector holds all the pattern separated by a unique string 
	//identifier.
	vector<vector<int> > combined_pattern;
	vector<int> vec;
	suffixtree_node *sft; //pointer to suffix tree root
	bfslist_suffixtree bfslist;//list holds nodes at each level.
	pattern mtf;
	bool yes_mtf;
	
	/*the matched motif position string is collected from each DNA 
	pattern by lex,merged with combined_pattern after adding a 
	unique string identifier (-ve integers)*/
	i = -1;
	do
	{
		yes_mtf = get_matched_motif(mtf);
		if(yes_mtf == true)
			vec = mtf;
			vec.push_back(i);
			i -= 1;
			combined_pattern.push_back(vec);
			vec.clear();
			
	}while(yes_mtf);
	
	//suffix tree is created for the combined pattern
	sft=create_stree(combined_pattern); 
	
	//level wise node list is created using bfs traversal.
	bfs(sft,bfslist);
	
	cout << "nodes : " << suffixtree_node_count<< endl;
	
	//do the preprocessing of suffx tree to compute lca values.
	preprocess_suffixtree(sft,bfslist);
	
	//compute final C values.
	create_cv(sft,combined_pattern.size(),bfslist);
	
	//display substrings 
	cout << "\nThe matching statistics is shown below.....\n";
	show_substrings(sft,combined_pattern);
	cout << endl;
	
	// free memories used
	free(H);
	free(S);
	free(U);
	free(C);
	free(lca_values);
	
	return 0;
}
