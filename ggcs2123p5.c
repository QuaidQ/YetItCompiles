#include "cs2123p5.h"
#include <stdio.h>

//Recursively search through the tree to find the matching ID
NodeT *findId(NodeT *p, char szId[])
{
    //base case
    if (p == NULL)
        return NULL;
    //if element is found, return node
    else if (szId == p->element.szId)
        return p;
    //if element type is an option, go to the child pointer
    else if (p->element.cNodeType == 'O')
        return findId(p->pChild, szId);
    //if element type is a value, go to the sibling
    else
        return findId(p->pSibling, szId);
}

/******************** allocateNodeT ****************************************
 NodeLL *allocateNodeT(LinkedList list, Event value)
 Purpose:
 
 Parameters:
 
 Returns:
 
 Notes:
 
 **************************************************************************/
NodeT *allocateNodeT(QuoteSelection quote, Element element)
{
    NodeT *pNew;
    pNew = (NodeT *)malloc(sizeof(NodeT));
    if (pNew == NULL)
        ErrExit(ERR_ALGORITHM, "No available memory for linked list.");
    pNew->element = element;
    pNew->pSibling = NULL;
    pNew->pChild = NULL;
    return pNew;
}

//Recursively search through the tree to find where to insert
NodeT *insertT(NodeT **pp, QuoteSelection quote, Element element)
{
    // if NULL, allocate a new node
    if (*pp == NULL)
    {
        *pp = allocateNodeT(quote, element);
        return *pp;
    }
    // if the ID's match, return the node
    if (element.szId == (*pp)->element.szId)
        return *pp;
    // if element type is an option, go to the child pointer
    if (element.cNodeType == 'O')
        return insertT(&(*pp)->pChild, quote, element);
    // else go to the sibling pointer
    else
        return insertT(&(*pp)->pSibling, quote, element);
}