/******************************************************************************
 cs2123p5JM.c by Justin Mungal
 
 Purpose:
  -Defines deleteItem and findParent functions
 
 Command Parameters:
 n/a
 Input:
 
 Results:
 
 Notes:
 *******************************************************************************/

#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include "cs2123p5.h"

void deleteItem(Tree tree, char szId[])
{
    NodeT *p;
    NodeT *pParent;
    
    p = findId(tree->pRoot, szId);
    
    //return if the node is null
    if (p == NULL)
    {
        printf("ERROR ID %s NOT FOUND\n", szId);
        return;
    }
    
    //recurse into child nodes
    deleteItem(tree, p->pChild->element.szId);
    
    //set parent pointer to null
    //insert call to find parent here
    //set parent->pChild value to null 
    
    //delete node
    free(p);
    
}

NodeT *findParent(NodeT *pParent, NodeT *p, NodeT *pkid)
{
    
}