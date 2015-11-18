#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include "cs2123p5.h"

/******************** prettyPrint ****************************************
 void prettyPrint(NodeT *p, int iIndent)
 Purpose: Prints the entire tree in a pretty print style 
 
 Parameters:
 I       NodeT *p                Pointer to a node 
 I       int iIndent             Indents when printing 
 
 Returns:
 N/A
 
 Notes:
**************************************************************************/
void prettyPrint(NodeT *p, int iIndent)
{
    int i;
    
    if(p == NULL)
        return; 
    
    prettyPrint(p->pChild, iIndent + 1);
    printf("\t");

    for (i = 0; i < iIndent; i++)
        printf("\t");
    //if it does not have a cost print just the item title
    if (p->element.cCostInd == 'N')
        printf("%s\n", p->element.szTitle);
    // if it does have a value print both item title and its cost 
    else
        printf("%s%.2lf\n", p->element.szTitle, p->element.dCost);
    prettyPrint(p->pSibling, iIndent + 1);
}
/********************printPriceMenu******************************
 void printPriceMenu(Tree tree)
 Purpose: Prints the contents of the tree in a readable style
 
 Parameters:
 I    Tree tree	Struct containing the Root and Nodes of a tree
 
 Returns:
 N/A
 
 Notes:
 **************************************************************************/
void printPriceMenu(Tree tree)
{
    NodeT *pRoot;
    pRoot = tree->pRoot;
    //call prettyPrint to print in pretty print style 
    prettyPrint(pRoot,0);
}
/********************printOne*************************************
 void printOne(Tree tree, char szId[])
 Purpose: Prints one item from the tree.  This is used from the PRINT ONE command
 
 Parameters:
 I      Tree tree               Struct containing the Root and Nodes of a tree.
 I/O      char szId[]             Element ID being printed.
 
 Returns:
 N/A
 Notes:
  **************************************************************************/
void printOne(Tree tree, char szId[])
{
    NodeT *p;
    p = findId(tree->pRoot, szId);

    if (p == NULL)
        printf("ERROR ID %s NOT FOUND\n", szId);
    else 
        printf("Title: %s Cost: %.2lf\n", p->element.szTitle, p->element.dCost);
}
