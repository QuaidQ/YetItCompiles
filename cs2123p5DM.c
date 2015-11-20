    #define _CRT_SECURE_NO_WARNINGS 1

    #include <stdio.h>
    #include <string.h>
    #include <stdarg.h>
    #include <stdlib.h>
    #include "cs2123p5.h"

    void commandDefine(Tree tree, QuoteSelection quote, char szRemainingTxt[])
    {
        //get second command to see if its Option or value
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

    void insertPriceMenu(Tree tree, Element element, char szParentId[]){
        //here we handle if the root is empty so we insert
     //to go down the list of roots sibilings until it hits null
                 //and inserts

        if(strcmp(szParentId,"ROOT")== 0){
           printf("parent ID is ROOT so inserting to the root\n\t");
            if(tree->pRoot == NULL){
                tree->pRoot = allocateNodeT(element);
                printf("element inserted in pROOt\n\n ");

           return;
            }
            //p is pointing to sibling of pROOT;

            if(tree->pRoot->pSibling == NULL){
                printf("Root SIBLING is empty, inserting here\n\n");
                tree->pRoot->pSibling = allocateNodeT(element);
                return;
                }
                return;
            }
    else{

        NodeT *p;

    //insertion at the tree handled
    //now normal insert

    // find parent...
        if (findId(tree->pRoot,szParentId) != NULL){
                 //found
                 //check if parent is the same as option
                 //or the item is already in the menu
                 if (findId(tree->pRoot,element.szId) != NULL){
                     printf("Item is already in the menu\n\t");
                return;
                 }
                 p = findId(tree->pRoot,szParentId);
                 p = insertT(&p->pChild,element);
            }
        else{
                printf("OOOPS NO PARENT FOUND\n\tcan't insert that");
                printf("\n\t");
                return;
        }
    }
    }
    void commandDelete(Tree tree, QuoteSelection quote, char szId[]){


     printf("Command DELETE processed. Item to be deleted: %s\n" ,szId );
       /******************************************
        * call Delete here                       *
        *****************************************/




     }
     /*************************************************************************/
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
            printf("command PRINT ALL obtained, need to call function\n\n");
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

            printf("command PRINT ONE obtained, need to call function\n");
            /*****************************************
             * call to print ONE here                 *
             *****************************************/
            printOne(tree,szId);
        }
    }
    /****************************************************************************/

    void processCommand(Tree tree, QuoteSelection quote, char szInputBuffer[]){
        /********
         command types
         1.DEFINE
         2.PRINT
         3.DELETE
         4.QUOTE
         *********************/
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
        }
    }
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

    /***********************************************************************/
