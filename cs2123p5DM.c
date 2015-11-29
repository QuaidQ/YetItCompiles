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

void insertPriceMenu(Tree tree, Element element, char szParentId[])
{
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
void commandDelete(Tree tree, QuoteSelection quote, char szId[])
{
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
void commandQuote(Tree tree,QuoteSelection quote , char szRemainingTxt[])
{

    char szsubComandType[16];
    char * pszRemainingTxt;

    //get subcommand
    pszRemainingTxt = getToken(szRemainingTxt, szsubComandType, sizeof(szsubComandType)-1);
    // continue through line of  input
    strcpy(szRemainingTxt, pszRemainingTxt);


    if (strcmp(szsubComandType, "BEGIN") == 0)
    {   //quote has begun
        QuoteBegun = TRUE;
        QuoteSelection quote = newQuoteSelection();
    }
    if (strcmp(szsubComandType, "OPTION") == 0)
    {
        if(QuoteBegun != TRUE)
            return;


       quote->quoteItemM[quote->iQuoteItemCnt] = createItem(tree , szRemainingTxt);

        printf("Item's iLevel:\t %d\n", quote->quoteItemM[quote->iQuoteItemCnt].iLevel);
        printf("Item's szOptionId:\t %s\n", quote->quoteItemM[quote->iQuoteItemCnt].szOptionId);
        printf("Item's iSelection:\t %d\n", quote->quoteItemM[quote->iQuoteItemCnt].iSelection);
        printf("Item's szTitle:\t %s\n",quote->quoteItemM[quote->iQuoteItemCnt].szTitle);
        printf("Item's dCost:\t %.2f\n", quote->quoteItemM[quote->iQuoteItemCnt].dCost);


       //add item
       qResult.dTotalCost = qResult.dTotalCost + quote->quoteItemM[quote->iQuoteItemCnt].dCost;

       quote->iQuoteItemCnt = quote->iQuoteItemCnt + 1;
       printf("count in array is %d\n", quote->iQuoteItemCnt);
       printf("Total cost: %.2f\n", qResult.dTotalCost);
    }

       if (strcmp(szsubComandType, "END") == 0)
    {
         if(QuoteBegun != TRUE)
            return;

        determineQuote(tree, quote);

        printf("END\n");

        qResult.dTotalCost =0.0;


    }

}
QuoteResult determineQuote(Tree tree, QuoteSelection quote)
{

    //print shit justin!
    //call your print function here
    printQuoteDetails(tree, quote);

    patialQuoteCheck(tree,quote);

    printf("Total cost: %40.2lf\n", qResult.dTotalCost);
    printf("*****************END PRINT QUOTE DETAILS*************************\n");

    free(quote);
    return qResult;
}

QuoteSelectionItem createItem(Tree tree, char szRemainingTxt[])
{
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
void processCommand(Tree tree, QuoteSelection quote, char szInputBuffer[])
{

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
void freeTree(Tree tree)
{
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
void printQuoteDetails(Tree tree, QuoteSelection quote)
{

    printf("*****************BEGIN PRINT QUOTE DETAILS*************************\n");
    int i;
    int j;
    int k;
    int iSelect;
    NodeT *pkid;
    NodeT *pParent, *p;

    for (i = 0; i < quote->iQuoteItemCnt; i++) {
        pParent = findId(tree->pRoot, quote->quoteItemM[i].szOptionId);
        //find the selection
        iSelect = quote->quoteItemM[i].iSelection;

            //printf("iselect is %d\n", iSelect);

        if (iSelect == 1) {
            pkid = pParent->pChild;
        }
        else {
            p = pParent->pChild;

            for (k = 0; k < iSelect; k++) {
                pkid = p;
                p = p->pSibling;

            }
        }
        //printf("%s\n", pParent->element.szTitle);

        // printf("");
        if (pParent->element.cCostInd == 'N') {
            if(quote->quoteItemM[i].iLevel == 0)
                printf("\n");
            if(quote->quoteItemM[i].iLevel == 1)
                printf("      ");
            if(quote->quoteItemM[i].iLevel == 2)
                printf("         ");


            printf("%-30s\n", pParent->element.szTitle);

            // if it does have a value print both item title and its cost
        }
        for (j = 0; j <= quote->quoteItemM[i].iLevel; j++) {
            printf("   ");
        }
        if (pkid->element.cCostInd == 'N') {
            printf("%-30s\n", pkid->element.szTitle);
            printf("here");

        } else {
            if(quote->quoteItemM[i].iLevel == 0)
                printf("");
            if(quote->quoteItemM[i].iLevel == 1)
                printf("      ");
            if(quote->quoteItemM[i].iLevel == 2)
                printf("         ");

            printf("%-30s%-8.2lf\n", pkid->element.szTitle, pkid->element.dCost);

        }

    }
    printf("\n");
    return;


}
void patialQuoteCheck(Tree tree, QuoteSelection quote)
{

    QuoteCheck quoteCheck = newQuoteCheck();
    QuoteCheckItem checkForItem;
    //find out how many 0 ilevels are in the quote array
    int i, iCount, j;
    NodeT * p;
    for(i=0; i < quote->iQuoteItemCnt; i++)
    { if(quote->quoteItemM[i].iLevel == 0){
            //item with level zero found
            printf("item with level zero found: %s \n", quote->quoteItemM[i].szOptionId);
            //find children and siblings of the child.
            p = getOption(tree, quote->quoteItemM[i].szOptionId, quote->quoteItemM[i].iSelection);
            printf("selecting : %s \n\t", p->element.szId);
            //store all possible choices of p in the array.
                //move p to the child of what your selecting
            p = p->pChild;

            if(p==NULL) {
                printf("no child/child siblings to analyze\n");
                break;
            }
            printf("possible child selection: %s \n\t", p->element.szId);

            strcpy(checkForItem.szOptionId , p->element.szId);
            checkForItem.iFound = 0;
            //checkForItem.maxSelection = /** function that returns number of child and silbings pf p .**/
            //stare into array
            quoteCheck->quoteCheckItemM[quoteCheck->iQuoteItemCnt] = checkForItem;
            quoteCheck->iQuoteItemCnt = quoteCheck->iQuoteItemCnt + 1;
            //keep filling in quoteCheck until theres no more siblings.
            //we were at the child now we go select all the siblings of that child
            p = p->pSibling;

                if(p==NULL) {
                    printf("no child/child siblings to analyze\n");
                    break;
                }


            while(p != NULL){

                printf("possible child slection: %s \n\t", p->element.szId);

                strcpy(checkForItem.szOptionId , p->element.szId);
                checkForItem.iFound = 0;

                //checkForItem.maxSelection = /** function that returns number of child and silbings pf p .**/
                //stare into array
                quoteCheck->quoteCheckItemM[quoteCheck->iQuoteItemCnt] = checkForItem;
                quoteCheck->iQuoteItemCnt = quoteCheck->iQuoteItemCnt + 1;

                p = p->pSibling;

            }

        }


    }

    //look through quote array and mark what options are there.
    for(i=0; i < quoteCheck->iQuoteItemCnt; i++){
        printf("looking for id %s in quote\n\t", quoteCheck->quoteCheckItemM[i].szOptionId);
        for (j = 0; j < quote->iQuoteItemCnt ; j++) {
            //printf("id in quote is %s\n\t", quote->quoteItemM[j].szOptionId);
            if (strcmp(quote->quoteItemM[j].szOptionId,quoteCheck->quoteCheckItemM[i].szOptionId ) == 0){
                printf("found!\n");
                quoteCheck->quoteCheckItemM[i].iFound = 1;
                break;
            }

        }
        if (quoteCheck->quoteCheckItemM[i].iFound == 0) {
            printf("NOT FOUND -> blame justin. just cause.\n its a partial quote:   ");
            qResult.returnCode = QUOTE_PARTIAL;
            strcpy(qResult.error.szOptionId,quoteCheck->quoteCheckItemM[i].szOptionId);
            
        }
    }
    // if the array has  a 0 and not followed 1 its incomplete,
    //if the array has a 0 and is followed by 1's i



}

/******************** newQuoteCheck **************************************
  QuoteSelection newQuoteCheck()
Purpose:
Allocates memory for a QuoteCheckImp and initializes it.
Parameters:
n/a
Notes:
- Checks for malloc memory allocation error.
Returns:
Returns a QuoteCheck.  Note that a QuoteCheck is simply a pointer to
a QuoteCheckImp.
 **************************************************************************/
QuoteCheck newQuoteCheck()
{
    QuoteCheck  quoteCheck = (QuoteCheck)malloc(sizeof(QuoteCheckImp));

    if (quoteCheck == NULL)
        ErrExit(ERR_ALGORITHM, "malloc allocation error for QuoteCheckImp");
    quoteCheck->iQuoteItemCnt = 0;
    return quoteCheck;
}