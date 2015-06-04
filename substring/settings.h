#define minMotifLen 6
#define minNumOfMotifInPat 20
#define minNoPat 10
#define MAX 20

#define MaxSubSeqLength 20

typedef vector<int> motif; // vector contains motifs(provided)
typedef vector<int> dna_pattern;  // vector contains original DNA patterns(provided)
typedef vector<int> pattern;  // vector contains the relative positions of matched motifs
//typedef set<motif> set_motif;
typedef vector<int> merged_pattern; //vector contains all the "pattern" separated by different end markers(-ve integer)
int clen; //critical length (cutoff) subsequence length must atleast clen.
