%%

[\t ]+;

ABDEGGKNP	{fprintf(yyout,"1,");}
BCDFGLMNOOOQRSTU	{fprintf(yyout,"2,");}
BBDDFFGG	{fprintf(yyout,"3,");}
ABCGKMQRTT	{fprintf(yyout,"4,");}
DEGKLMNOPQR	{fprintf(yyout,"5,");}
CDEFGJLOOPQRSSST	{fprintf(yyout,"6,");}
FGHHIP	{fprintf(yyout,"7,");}
PPQSTTUV	{fprintf(yyout,"8,");}
EKLOPQRS	{fprintf(yyout,"9,");}
AACDIKTU	{fprintf(yyout,"10,");}

.
%%
extern FILE *yyin,*yyout;
main()
{
yyin=fopen("pattern","r");
yyout=fopen("matched_motif","w");

yylex();
}