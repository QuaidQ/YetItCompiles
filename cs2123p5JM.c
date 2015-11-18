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
        return;
    
    //recurse into child nodes
    deleteItem(tree, p->pChild->element.szId);
    
    //recurse into sibling nodes
    deleteItem(tree, p->pSibling->element.szId);
    
    //set the parent node's reference to NULL
    findParent(pParent, tree->pRoot, p);
    pParent->pChild = NULL;
    
    //delete node
    free(p);
    
}

NodeT *findParent(NodeT *pParent, NodeT *p, NodeT *pkid)
{
    //base case
    if (p == NULL || pkid == NULL)
        return NULL;
    
    //check to see if we've found the matching parent
    if (pParent->pChild == pkid)
        return pParent;
    
    //recurse into sibling node if one exists
    if (p->pSibling != NULL)
        return findParent(pParent, p->pSibling, pkid);
    
    //recurse into child node if one exists
    if (p->pChild != NULL)
        return findParent(p, p->pChild, pkid);
    
    //no match if we're here
    return NULL;
}