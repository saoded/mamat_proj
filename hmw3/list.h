#ifndef _LIST_H_
#define _LIST_H_

#include "defs.h"
#include <stdio.h>
#include <stdlib.h>

typedef void* PElement;
typedef PElement (*CloneElem)(const PElement); // signature of clone function
typedef void (*DestroyElem)(const PElement); // signature of free function
typedef BOOL (*CompareElem)(const PElement, const PElement); // signature of compare function
typedef void (*PrintElem)(const PElement); // signature of print function

// Node will encapsulate the Element for iterations through the list
typedef struct Node_{
    struct Node_* pPrev; // two-way list boosts Element removal & more
    struct Node_* pNext;
    PElement pValue;
} Node;
typedef Node* PNode;

typedef struct List_
{
    PNode head; // first Node in list
    PNode tail; // last Node in list
    PNode iterator; // Last fetched Node
    int size; // current number of elements

    // Functions that will be different for different types of elements
    CloneElem cloneFunc;
    DestroyElem destroyFunc;
    CompareElem compareFunc;
    PrintElem printFunc;
} List;
typedef List* PList;

///////////////////////////////////////////////////////////////////////////////////////
// function name : ListCreate                                                       //
// description   : creates a List ADT with the input properties                    //
// parameters    : CloneElem   - a function to copy elements of the list          //
//                 DestroyElem - a function to free elements of the list         //
//                 CompareElem - a function to compare two elements of the list //
//                 PrintElem   - a function which prints elemnts of the list   //
// retrun value  : returns a pointer to the created List ADT, NULL if fails   //
///////////////////////////////////////////////////////////////////////////////
PList ListCreate(const CloneElem, const DestroyElem, const CompareElem, const PrintElem);
//////////////////////////////////////////////////////////////
// function name : ListDestroy                             //
// description   : Frees a List ADT and all its elements  //
// parameters    : PList - points to the List to destroy //
// retrun value  : none                                 //
/////////////////////////////////////////////////////////
void ListDestroy(PList);
////////////////////////////////////////////////////////////////////////
// function name : ListAdd                                           //
// description   : adds a copy of input element to a List ADT       //
// parameters    : PList    - the list to which we add             //
//                 PElement - the added element                   //
// retrun value  : SUCCESS if added successfully, FAIL otherwise //
//////////////////////////////////////////////////////////////////
Result ListAdd(PList, PElement);
////////////////////////////////////////////////////////////////////////////////////////////////
// function name : ListRemove                                                                //
// description   : removes each element which compares to the input element from a List ADT //
// parameters    : PList    - the list from which we remove                                //
//                 PElement - the element to remove                                       //
// retrun value  : SUCCESS if removed successfully, FAIL otherwise                       //
//////////////////////////////////////////////////////////////////////////////////////////
Result ListRemove(PList, PElement);
///////////////////////////////////////////////////////////////////////////////////////////
// function name : ListGetFirst                                                         //
// description   : bring a List ADT iterator to the beginning and return first element //
// parameters    : PList - the list we operate with                                   //
// retrun value  : a pointer to the first element in the list                        //
//////////////////////////////////////////////////////////////////////////////////////
PElement ListGetFirst(PList);
///////////////////////////////////////////////////////////////////////////
// function name : ListGetNext                                          //
// description   : promote a List ADT iterator and return next element //
// parameters    : PList - the list we operate with                   //
// retrun value  : a pointer to the next element in the list         //
//////////////////////////////////////////////////////////////////////
PElement ListGetNext(PList);
////////////////////////////////////////////////////////////////
// function name : ListCompare                               //
// description   : compares two List ADTs                   //
// parameters    : PList - 1st list                        //
//                 PList - 2nd list                       //
// retrun value  : TRUE if lists have the same elements, //
//                 FALSE otherwise                      //
/////////////////////////////////////////////////////////
BOOL ListCompare(const PList, const PList);
/////////////////////////////////////////////////////////
// function name : ListPrint                          //
// description   : prints each element in a List ADT //
// parameters    : PList - the list we operate with //
// retrun value  : none                            //
////////////////////////////////////////////////////
void ListPrint(const PList);

/////////////////////////////////////////////////////////////////
// function name : ListFind                                   //
// description   : gets the node of an element in a List ADT //
// parameters    : PList    - the list we operate with      //
//                 PElement - the element to find          //
// retrun value  : a pointer to the containing node       //
//                 NULL if not found                     //
//////////////////////////////////////////////////////////
PNode ListFind(PList, const PElement);
//////////////////////////////////////////////////////////////////////////
// function name : ListRemoveNode                                      //
// description   : removes a Node from a List ADT                     //
// parameters    : PList - the List from which we remove             //
//                 PNode - the Node to remove                       //
// retrun value  : SUCCESS if removed successfully, FAIL otherwise //
////////////////////////////////////////////////////////////////////
Result ListRemoveNode(PList, PNode);
///////////////////////////////////////////////////////////////////
// function name : ListGetSize                                  //
// description   : return the number of elements in a list ADT //
// parameters    : PList - the list we operate with           //
// retrun value  : number of elements in list                //
//////////////////////////////////////////////////////////////
int ListGetSize(const PList);

#endif
