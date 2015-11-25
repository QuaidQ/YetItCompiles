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
    printf("Beginning deleteItem call on szId %s\n", szId);
    NodeT *p;
    NodeT *pParent;
    
    p = findId(tree->pRoot, szId);

    //return if the node is null
    if (p == NULL)
    {
        printf("Null node, returning!\n");
        return;
    }
    else
    {
        printf("p set to: %s\n", p->element.szId);
    }

    //recurse into child node if one exists
    if (p->pChild != NULL)
    {
        printf("recursing into child %s\n",p->pChild->element.szId);

        //recurse into the child's sibling node if one exists
        if (p->pChild->pSibling != NULL)
        {
            printf("recursing into child sibling %s\n", p->pChild->pSibling->element.szId);
            deleteItem(tree, p->pChild->pSibling->element.szId);
        }

        deleteItem(tree,p->pChild->element.szId);
    }

    //get the parent of p
    pParent = findParent(pParent, tree->pRoot, p);
    printf("pParent set to: %s\n", pParent->element.szId);

    //If p has a sibling, update the parent node to point to it
    if (p->pSibling != NULL)
    {
        printf("setting parent's child to the child's sibling, %s\n",p->pSibling->element.szId);
        pParent->pChild = p->pSibling;
    }
        //otherwise set it to null to prevent a dangling reference
    else
    {
        printf("setting the parent's child pointer to null\n");
        pParent->pChild = NULL;
    }

    //delete node
    printf("deleting %s.\n",p->element.szId);
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

    if (findId(p, pkid->element.szId) != NULL);
    {
        //check to see if we've found the matching parent
        if (p == pkid)
            return pParent;

        //recurse into sibling node if one exists
        if (p->pSibling != NULL) {
            //in this call, the sibling node is now p
            pTemp = findParent(pParent, p->pSibling, pkid);

            //return pTemp if it's not NULL
            if (pTemp != NULL)
                return pTemp;
        }

        //recurse into child node if one exists
        if (p->pChild != NULL) {
            //in this call, p is the new parent, and the child node is the new p
            pTemp = findParent(p, p->pChild, pkid);

            //return pTemp if it's not NULL
            if (pTemp != NULL)
                return pTemp;
        }
    }

    return NULL;

}