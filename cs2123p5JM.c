/******************************************************************************
 cs2123p5JM.c by Justin Mungal
 
 Purpose:
  -Defines deleteItem and findParent functions
  -test
 
 *******************************************************************************/
#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include "cs2123p5.h"

/******************** deleteItem ******************************************
 void deleteItem(Tree tree, char szId[])
 
 Purpose:
 Deletes a node from the tree, and all sub-nodes. Removes the reference to 
 the removed node in the parent.
 
 Parameters:
 I/O    Tree tree               The tree we are modifying
 I      char szId[]             The unique character identifier for the
                                node being removed.
 Returns:
 N/A
 
 Notes:
 N/A
 **************************************************************************/
void deleteItem(Tree tree, char szId[])
{
    NodeT *p;
    NodeT *pParent;
    
    p = findId(tree->pRoot, szId);
    
    //return if the node is null
    if (p == NULL)
        return;
    
    //recurse into child node if one exists
    if (p->pChild != NULL)
        deleteItem(tree, p->pChild->element.szId);
    
    //recurse into sibling node if one exists
    if (p->pSibling != NULL)
        deleteItem(tree, p->pSibling->element.szId);
    
    //set the parent node's reference to the child node to NULL
    pParent = findParent(NULL, tree->pRoot, p);
    pParent->pChild = NULL;
    
    //delete node
    free(p);
}

/******************** findParent ******************************************
 NodeT *findParent(NodeT *pParent, NodeT *p, NodeT *pkid)
 
 Purpose:
 Find the parent node of a specified child node.
 
 Parameters:
 I/O    NodeT *pParent
 I      NodeT *p
 I      NodeT *pkid
 
 Returns:
 Returns the parent node, if one is found, via *pParent in the parameter
 list. If no parent is found, NULL is returned.
 
 Notes:
 When you call this function, pkid will be the node who's parent you want
 to find, and p will be the root of tree. We call the function with the root 
 of the tree because we need to traverse the tree since there is no
 pointer in the child to the parent. *pParent would just be empty when
 you call the function. 
 
 An example call:
 findParent(pParent, tree->pRoot, p);
 **************************************************************************/
NodeT *findParent(NodeT *pParent, NodeT *p, NodeT *pkid)
{
    NodeT *pTemp;
    
    //base case
    if (p == NULL)
        return NULL;
    
    //check to see if we've found the matching parent
    if (p == pkid)
        return pParent;
    
    //recurse into sibling node if one exists
    if (p->pSibling != NULL)
        //in this call, the sibling node is now p
        pTemp = findParent(pParent, p->pSibling, pkid);
    
    //recurse into child node if one exists
    if (p->pChild != NULL)
        //in this call, p is the new parent, and the child node is the new p
        pTemp = findParent(p, p->pChild, pkid);
    
    //Return what was found, whether it's the Node or NULL
    return pTemp;
}