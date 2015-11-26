/******************************************************************************
 cs2123p5JM.c by Justin Mungal

 Purpose:
  -Defines deleteItem, findParent, and findPredSibling

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
    NodeT *p, *pParent, *pSibling, *pPredSibling;

    p = findId(tree->pRoot, szId);

    //return if the node is null
    if (p == NULL)
        return;

    //get the parent of p
    pParent = findParent(pParent, tree->pRoot, p);

    //get the predecessor sibling
    pPredSibling = findPredSibling(tree->pRoot, p);

    //if the node we are deleting has a sibling, set that as the predecessor sibling's new sibling
    //otherwise set it to NULL to remove the dangling reference
    if (p->pSibling != NULL)
    {
        pSibling = p->pSibling;

        if (pPredSibling != NULL)
            pPredSibling->pSibling = pSibling;
    }
    else
        pPredSibling->pSibling = NULL;

    //update parent pointer if it points to the deleted node
    if (pParent->pChild == p)
    {
        if (pPredSibling != NULL)
            pParent->pChild = pPredSibling;
        else
            pParent->pChild = pSibling;
    }
    //delete nodes
    freeSubTree(p->pChild);
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

    //return null if p does not have a valid szId
    if (findId(p, pkid->element.szId) != NULL)
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
/******************** findPredSibling ****************************************
 NodeT *findPredSibling(NodeT *p, NodeT *pPredSibling)

 Purpose: Finds and returns a pointer to a node that has pSiblingNode
          as it's sibling (the predecessor sibling node).

 Parameters:
 I/O     NodeT *p                A node pointer from which to start searching
                                 and comparing.
 I       NodeT *pSiblingNode     The sibling node we are searching for. We are
                                 trying to find a predecessor node for it.

 Returns:
 p       The predecessor sibling node, if it exists.

 Notes:
 -Will traverse entire tree if necessary.
 **************************************************************************/
NodeT *findPredSibling(NodeT *p, NodeT *pSiblingNode)
{
    //temp NodeT to not over write pointer
    NodeT *pFound = NULL;

    //base case
    if (p == NULL)
        return NULL;

    //if element is found, return node
    if(p->pSibling != NULL && p->pSibling == pSiblingNode)
        return p;

    //recurse through the tree to find the element
    //search for element in the children
    pFound = findPredSibling(p->pChild, pSiblingNode);

    if (pFound != NULL)
        return pFound;

    //search through the siblings
    pFound = findPredSibling(p->pSibling, pSiblingNode);
    return pFound;
}
/******************** getOption ****************************************
 NodeT *getOption(Tree tree, char szId[], int iSelection)

 Purpose: searches for an option node, and returns a pointer to it if it's
    found.

 Parameters:
 I      Tree tree               The tree that will be searched
 I      char szId[]             The parent optionId
 I      int iSelection          Identifier of child or sibling

 Returns:
 pOption                        The option node, if found
 **************************************************************************/
NodeT *getOption(Tree tree, char szId[], int iSelection)
{
    NodeT *p, *pOption;
    int i;

    p = findId(tree->pRoot, szId);

    //return if called with invalid szId or an iSelection less than 1
    if (p == NULL || p->pChild == NULL || iSelection < 1)
        return NULL;

    if (iSelection == 1)
    {
        pOption = p->pChild;
        return pOption;
    }

    //if iSelection is 1 or more, start traversing child siblings
    p = p->pChild;

    for(i=2; i<=iSelection; i++)
    {
        p = p->pSibling;

        if (p == NULL)
            return NULL;

        pOption = p;
    }

    return pOption;
}
