#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include "cs2123p5.h"
/*********************commandDefine****************************************
  void commandDefine(Tree tree, QuoteSelection quote, char szRemainingTxt[])
purpose:
the function is called after a command DEFINE has been initiated.
We find out the rest of the buffer
see if its and option or value
place buffer info into the element. then it calls insertPriceMenu passing it
the tree, element made and the elements parentId
Parameters:
I Tree tree     tree of menu to be inserted to and printed off
I QuoteSelection quote   quote to the menu to be inserted and printed off
I char szRemainingTxt[]  buffer after you've taken out the initial define command
Returns:
N/A
Notes:

 *************************************************************************/
void commandDefine(Tree tree, QuoteSelection quote, char szRemainingTxt[])
{    //get second command to see if its Option or value
        char szsubComandType[16];
        char *pszRemainingTxt;
        //items to be read into the element
        char parentsNodesID[16] = "";
        char costIden[5];
        char costValue[16];


        //element to be inserted into tree
        Element element;
        //get subcommand
        pszRemainingTxt = getToken(szRemainingTxt, szsubComandType, sizeof(szsubComandType)-1);
        // continue through line of  input
        strcpy(szRemainingTxt, pszRemainingTxt);


        if (strcmp(szsubComandType, "OPTION") == 0)
        {
            element.cNodeType = 'O';
                element.cCostInd = 'N';
                //getID of node
                pszRemainingTxt = getToken(szRemainingTxt, element.szId, sizeof(element.szId)-1);
                strcpy(szRemainingTxt, pszRemainingTxt);
                //get ID of it's parent
                pszRemainingTxt = getToken(szRemainingTxt, parentsNodesID, sizeof(parentsNodesID)-1);
                strcpy(szRemainingTxt, pszRemainingTxt);
                //get the title for node
                pszRemainingTxt = getToken(szRemainingTxt, element.szTitle, sizeof(element.szTitle)-1);
                strcpy(szRemainingTxt, pszRemainingTxt);
                //element completed ready to be inserted
                insertPriceMenu(tree,element,parentsNodesID);

        }
        else if(strcmp(szsubComandType, "VALUE") == 0)
        {
                element.cNodeType = 'V';
                element.cCostInd = 'Y';

                //getID of node
                pszRemainingTxt = getToken(szRemainingTxt, element.szId, sizeof(element.szId)-1);
                strcpy(szRemainingTxt, pszRemainingTxt);

                //get ID of it's parent
                pszRemainingTxt = getToken(szRemainingTxt, parentsNodesID, sizeof(parentsNodesID)-1);
                strcpy(szRemainingTxt, pszRemainingTxt);


                //get cost identification
                pszRemainingTxt = getToken(szRemainingTxt,costIden, sizeof(costIden)-1);
                strcpy(szRemainingTxt, pszRemainingTxt);



                //get cost
                pszRemainingTxt = getToken(szRemainingTxt, costValue , sizeof(costValue)-1);
                strcpy(szRemainingTxt, pszRemainingTxt);
                sscanf(costValue, "%lf" , &element.dCost);


                //get the title for node

                // pszRemainingTxt = getToken(szRemainingTxt, element.szTitle, sizeof(element.szTitle)-1);
                //strcpy(szRemainingTxt, pszRemainingTxt);
                strcpy(element.szTitle,szRemainingTxt);
                stripNewline(element.szTitle, 30);

                //element completed, ready to be inserted
                insertPriceMenu(tree,element,parentsNodesID);

        }

        /***************************************************
         * element has been filled and ready to be inserted.*
         ****************************************************/

        //call insert here

        return;
}
/*********************commandDefine****************************************
  void commandDefine(Tree tree, QuoteSelection quote, char szRemainingTxt[])
purpose:
to insert into the tree.
first takes care of the root being empty.
once the root is not empty in branches off from them, inserting at childs
and siblings.
Parameters:
I Tree tree     tree of menu to be inserted to and printed off
I QuoteSelection quote   quote to the menu to be inserted and printed off
I char szParentId[]  id of the nodes parent to be inserted
Returns:
N/A
Notes:
handles diffrent types of inserting errors that user might place
 ************************************************************************/

void insertPriceMenu(Tree tree, Element element, char szParentId[]){
    //here we handle if the root is empty so we insert
    //to go down the list of roots sibilings until it hits null
    //and inserts

        if(strcmp(szParentId,"ROOT")== 0){
            //printf("parent ID is ROOT so inserting to the root\n\t");
            if(tree->pRoot == NULL){
                tree->pRoot = allocateNodeT(element);
                    //          printf("element inserted in pROOt\n\n ");
                    return;
            }
            //p is pointing to sibling of pROOT;

                if(tree->pRoot->pSibling == NULL){
                    //    printf("Root SIBLING is empty, inserting here\n\n");
                    tree->pRoot->pSibling = allocateNodeT(element);
                        return;
                }
            return;
        }
        else{
               // NodeT *p;
                NodeT *pParent;
                //insertion at the tree handled
                //now normal insert
                // find parent...
                if (findId(tree->pRoot,szParentId) != NULL){
                    //found
                    //check if parent is the same as option
                    //or the item is already in the menu
                    if (findId(tree->pRoot,element.szId) != NULL){
                   //    ErrExit(ERR_DATA, "Option trying to be inserted is already in the Menu");
                       printf("Item is already in the menu\n\t");
                            return;
                    }
                    pParent = findId(tree->pRoot,szParentId);
                    //this if statement handles value into value
                    if(pParent->element.cNodeType == 'V' && element.cNodeType == 'V'){
                        printf("\tCan't insert a value into a value!\n\t");
                    return;
                    }
                    insertT(&pParent->pChild,element);
                }
                else{
                   // ErrExit(ERR_DATA, "Option trying to be inserted at wrong place, wrong parent ID from Input.");
                     printf("OOOPS NO PARENT FOUND. Can't insert that");
                        printf("\n");
              return;


                }
        }
}

/*********************commandDelete****************************************
  void commandDelete(Tree tree, QuoteSelection quote, char szId[])
  purpose:
  the function is called after a command DELETE has been initiated.
  We find out the rest of the buffer
  Call a function to delete with!
  Parameters:
  I Tree tree     tree of menu to be inserted to and printed off
  I QuoteSelection quote   quote to the menu to be inserted and printed off
  I char szId[]   id of element to be deleted
  Returns:
  N/A
 Notes:

 *************************************************************************/
void commandDelete(Tree tree, QuoteSelection quote, char szId[]){
    //      printf("Command DELETE processed. Item to be deleted: %s\n" ,szId );
    /******************************************
     * call Delete here                       *
     *****************************************/
}
/*********************commandDefine****************************************
  void command(Tree tree, QuoteSelection quote, char szRemainingTxt[])
purpose:
the function is called from the driver that gets a line of input
Its passed a line of input and it gets the first command of the line
 ********
 command types
 1.DEFINE
 2.PRINT
 3.DELETE
 4.QUOTE
 ********
 calls different functions depending of the type of command.
Parameters:
I Tree tree     tree of menu to be inserted to and printed off
I QuoteSelection quote   quote to the menu to be inserted and printed off
I char szRemainingTxt[]  buffer after you've taken out the initial define command
Returns:
N/A
Notes:

 *************************************************************************/
void commandPrint(Tree tree, QuoteSelection quote, char szRemainingTxt[])
{
    //items for getToken
    char szsubComandType[16];
    char szId[32];
    char *pszRemainingTxt;

    //get subcommand
    pszRemainingTxt = getToken(szRemainingTxt, szsubComandType, sizeof(szsubComandType)-1);
    // continue through line of  input
    strcpy(szRemainingTxt, pszRemainingTxt);

    if (strcmp(szsubComandType, "ALL") == 0)
    {
        //  printf("command PRINT ALL obtained, need to call function\n\n");
        /*****************************************
         * call to print all here                 *
         *****************************************/
        printPriceMenu(tree);
    }
    if (strcmp(szsubComandType, "ONE") == 0)
    {
        //get szID to which print
        pszRemainingTxt = getToken(szRemainingTxt, szId, sizeof(szId)-1);
        strcpy(szRemainingTxt, pszRemainingTxt);

        //printf("command PRINT ONE obtained, need to call function\n");
        printOne(tree,szId);
    }
}
void commandQuote(Tree tree,QuoteSelection quote , char szRemainingTxt[]){

    char szsubComandType[16];
    char * pszRemainingTxt;

    //get subcommand
    pszRemainingTxt = getToken(szRemainingTxt, szsubComandType, sizeof(szsubComandType)-1);
    // continue through line of  input
    strcpy(szRemainingTxt, pszRemainingTxt);


    if (strcmp(szsubComandType, "BEGIN") == 0)
    {   //quote has begun
        QuoteBegun = TRUE;
    }
    if (strcmp(szsubComandType, "OPTION") == 0)
    {
        if(QuoteBegun != TRUE)
            return;


       quote->quoteItemM[quote->iQuoteItemCnt] = createItem(tree , quote, szRemainingTxt);

        printf("Item's iLevel:\t %d\n", quote->quoteItemM[quote->iQuoteItemCnt].iLevel);
        printf("Item's szOptionId:\t %s\n", quote->quoteItemM[quote->iQuoteItemCnt].szOptionId);
        printf("Item's iSelection:\t %d\n", quote->quoteItemM[quote->iQuoteItemCnt].iSelection);
        printf("Item's szOptionId:\t %s\n",quote->quoteItemM[quote->iQuoteItemCnt].szOptionId);
        printf("Item's szTitle:\t %s\n",quote->quoteItemM[quote->iQuoteItemCnt].szTitle);
        printf("Item's dCost:\t %.2f\n", quote->quoteItemM[quote->iQuoteItemCnt].dCost);


       //add item
       quote->iQuoteItemCnt = quote->iQuoteItemCnt + 1;
       printf("count in array is %d\n", quote->iQuoteItemCnt);
   // printf("whats in the array? : %d ", quote->quoteItemM[quote->iQuoteItemCnt].dCost);
    }

       if (strcmp(szsubComandType, "END") == 0)
    {
        printf("END\n");
    }




}


QuoteSelectionItem createItem(Tree tree ,QuoteSelection quote, char szRemainingTxt[]){
    printf("OPTION\n");


    char sziLevel[16];
    //char cszOptionID[MAX_ID_SIZE+1];
    char sziSelection[16];
    char * pszRemainingTxt;

    NodeT * p;
    QuoteSelectionItem Item;

    //get iLevel token
    pszRemainingTxt = getToken(szRemainingTxt, sziLevel,sizeof(sziLevel)-1);
    // continue through line of  input
    strcpy(szRemainingTxt, pszRemainingTxt);

    //get iLevel token
    pszRemainingTxt = getToken(szRemainingTxt, Item.szOptionId,sizeof(Item.szOptionId)-1);
    // continue through line of  input
    strcpy(szRemainingTxt, pszRemainingTxt);
    //get iLevel token
    pszRemainingTxt = getToken(szRemainingTxt, sziSelection,sizeof(sziSelection)-1);
    // continue through line of  input
    strcpy(szRemainingTxt, pszRemainingTxt);

    //sscanf(costValue, "%d" , &element.dCost);
    sscanf(sziLevel, "%d", &Item.iLevel);
    sscanf(sziSelection, "%d", &Item.iSelection);
    //call dCost
    p = getOption(tree, Item.szOptionId, Item.iSelection);

    //Item.szId = *p->element.szId;
    strcpy(Item.szTitle , p->element.szTitle);
    Item.dCost= p->element.dCost;

return Item;
}
/*********************processCommand**********************************
  void processCommand(Tree tree, QuoteSelection quote, char szInputBuffer[])
purpose:
the function is called after a command DEFINE has been initiated.
We find out the rest of the buffer
see if its and option or value
place buffer info into the element. then it calls insertPriceMenu passing it
the tree, element made and the elements parentId
Parameters:
I Tree tree     tree of menu to be inserted to and printed off
I QuoteSelection quote   quote to the menu to be inserted and printed off
I char szRemainingTxt[]  buffer after you've taken out the initial define command
Returns:
N/A
Notes:

 *************************************************************************/
void processCommand(Tree tree, QuoteSelection quote, char szInputBuffer[]){

        char szCommandType[16];
        char *pszRemainingTxt;
        char szRemainingTxt[200];

        //get command
        pszRemainingTxt = getToken(szInputBuffer, szCommandType, sizeof(szCommandType)-1);

        // continue through line of  input
        strcpy(szRemainingTxt, pszRemainingTxt);

        if (strcmp(szCommandType, "DEFINE") == 0){
            commandDefine(tree,quote, szRemainingTxt);
        }

        if(strcmp(szCommandType, "PRINT") == 0){
            commandPrint(tree, quote,szRemainingTxt);
        }
        if(strcmp(szCommandType, "DELETE") == 0){
        commandDelete(tree, quote , szRemainingTxt);
        }
        if(strcmp(szCommandType, "QUOTE") == 0){
        commandQuote(tree, quote , szRemainingTxt);
        }
}
/*********************freeSubTree*****************************
  void freeTree(NodeT*p)
purpose:
recurse through tree and frees it
just frees the top of tree calls upon freeSubTree to take care
of the bottom first!
Parameters:
I Tree tree
Returns:
N/A
Notes:
 *************************************************************************/
void freeTree(Tree tree){
   freeSubTree(tree->pRoot);
   tree->pRoot = NULL;
    return;
}
/*********************freeSubTree*****************************
  void freeSubTree(NodeT*p)
purpose:
recurse through tree and frees it
Parameters:
I/O NodeT *P pointer to the tree
Returns: p
N/A
Notes:
 *************************************************************************/
void freeSubTree(NodeT * p)
{
    if( p == NULL)
        return;

   freeSubTree(p->pSibling);
   freeSubTree(p->pChild);

   free(p);
    return;
}
/*********************stripNewLine*****************************
  void stripNewline( char *str, int size)
purpose:
function is called to delete the new line from a string
\n => \o
Parameters:
I/O char * str  string to be used
I  int size     size of string
Returns:
N/A
Notes:

 *************************************************************************/
void stripNewline( char *str, int size)
{
    int i;
        for (  i = 0; i < size; ++i )
        {
            if ( str[i] == '\n' )
            {
                str[i] = '\0';
                    return;
            }
        }
}

