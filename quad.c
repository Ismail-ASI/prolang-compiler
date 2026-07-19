#include "quad.h"

qdr quad[1000];
int qc = 0;

void quadr(char opr[], char op1[], char op2[], char res[])
{
    strcpy(quad[qc].oper, opr);
    strcpy(quad[qc].op1,  op1);
    strcpy(quad[qc].op2,  op2);
    strcpy(quad[qc].res,  res);
    qc++;
}

void updateQuad(int num_quad, int colon_quad, char val[])
{
    if      (colon_quad == 0) strcpy(quad[num_quad].oper, val);
    else if (colon_quad == 1) strcpy(quad[num_quad].op1,  val);
    else if (colon_quad == 2) strcpy(quad[num_quad].op2,  val);
    else if (colon_quad == 3) strcpy(quad[num_quad].res,  val);
}

void afficher_qdr()
{
    printf("*********************Les Quadruplets***********************\n");
    printf("____________________________________________________________\n");
    int i;
    for(i = 0; i < qc; i++)
    {
        printf("\n %d - ( %s  ,  %s  ,  %s  ,  %s )", i,
               quad[i].oper, quad[i].op1, quad[i].op2, quad[i].res);
        printf("\n--------------------------------------------------------\n");
    }
}

