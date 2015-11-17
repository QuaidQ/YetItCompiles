#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include "cs2123p5.h"

void prettyPrint(NodeT *p, int iIndent)
{
    int i;
    
    if(p == NULL)
        return; 
    
    prettyPrint(p->pChild, iIndent + 1);
    printf("\t");

    for (i = 0; i < iIndent; i++)
        printf("\t");

    if (p->element.cCostInd == 'N')
        printf("%s\n", p->element.szTitle);
    else
        printf("%s%.2lf\n", p->element.szTitle, p->element.dCost);
    prettyPrint(p->pSibling, iIndent + 1);
}
void printPriceMenu(Tree tree)
{
    NodeT *pRoot; 
    pRoot = tree->pRoot;
    prettyPrint(pRoot,0);
}

void printOne(Tree tree, char szId[])
{
    NodeT *p;
    p = findId(tree->pRoot, szId);

    if (p == NULL)
        printf("ERROR ID %s NOT FOUND\n", szId);
    else 
        printf("Title: %s Cost: %.2lf\n", p->element.szTitle, p->element.dCost);
}
