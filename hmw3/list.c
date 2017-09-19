#include "list.h"

PList ListCreate(const CloneElem cln_f, const DestroyElem dstr_f, const CompareElem cmpr_f, const PrintElem prnt_f){
    // allocate the ADT
    PList newList = (PList)malloc(sizeof(List));
    if(newList == NULL){
        return NULL;
    }
    // initialize properties
    newList->head = NULL;
    newList->tail = NULL;
    newList->iterator = NULL;
    newList->size = 0;
    // assign functions
    newList->cloneFunc = cln_f;
    newList->destroyFunc = dstr_f;
    newList->compareFunc = cmpr_f;
    newList->printFunc = prnt_f;

    return newList;
}

Result ListAdd(PList list, PElement newElem){
    // no NULL pointer
    if(list == NULL || newElem == NULL){
        return FAIL;
    }
    // allocate encapsulating Node
    PNode cloneDestination = (PNode)malloc(sizeof(Node));
    if(cloneDestination == NULL){
        return FAIL;
    }
    // fill the Node
    cloneDestination->pValue = list->cloneFunc(newElem);
    if(cloneDestination->pValue == NULL){
        free(cloneDestination);
        return FAIL;
    }
    // put Node at the end of List
    cloneDestination->pNext = NULL;
    cloneDestination->pPrev = list->tail;
    // Put in head if List is empty, o.w. put after tail
    (list->size == 0) ? (list->head = cloneDestination) : (list->tail->pNext = cloneDestination);
    // Adjust tail and size
    list->tail = cloneDestination;
    ++(list->size);

    return SUCCESS;
}

PNode ListFind(PList list, const PElement elem){
    PNode n;
    for(n = list->head; n != NULL; n = n->pNext){
        if(list->compareFunc(n->pValue, elem) == TRUE){
            return n;
        }
    }
    return NULL; // if not found
}

Result ListRemoveNode(PList list, PNode n){
    if (n == NULL){
        return FAIL;
    }
    BOOL isHead = (n == list->head);
    BOOL isTail = (n == list->tail);
    // connect the list over the element to remove
    if(!isHead){
        n->pPrev->pNext = n->pNext;
    }
    if(!isTail){
        n->pNext->pPrev = n->pPrev;
    }
    // adjust head and tail if needed
    if(isHead){
        list->head = list->head->pNext;
    }
    if(isTail){
        list->tail = list->tail->pPrev;
    }
    // destroy the element
    list->destroyFunc(n->pValue);
    free(n);
    --(list->size);
    return SUCCESS;
}

Result ListRemove(PList list, const PElement elementToRemove){
    // no NULL ptrs
    if(list == NULL || elementToRemove == NULL){
        return FAIL;
    }
    // get the Node and remove it
    PNode n = ListFind(list, elementToRemove); 
    return ListRemoveNode(list, n);
}

void ListDestroy(PList list){
    // no NULL ptr
    if(list == NULL){
        return;
    }
    // remove all Nodes
    while(list->size != 0){
        ListRemoveNode(list, list->head);
    }
    free(list);
}

PElement ListGetFirst(PList list){
    // no NULL ptr
    if(list == NULL){
        return NULL;
    }
    // move iterator to head and return it
    list->iterator = list->head;
    return list->iterator->pValue;
}

PElement ListGetNext(PList list){
    // no NULL ptr, no NULL iterator.
    // also, when iterator is at tail, return NULL;
    if(list == NULL || list->iterator == NULL || list->iterator->pNext == NULL){
        return NULL;
    }
    // promote iterator and return its element
    list->iterator = list->iterator->pNext;
    return list->iterator->pValue;
}

BOOL ListCompare(const PList list1, const PList list2){
    // no NULL ptrs
    if(list1 == NULL || list2 == NULL){
        return FALSE;
    }
    PNode elem1;
    PNode elem2;
    // Make sure all elements are equal and in order
    for (elem1 = list1->head, elem2 = list2->head; elem1 != NULL && elem2 != NULL; elem1 = elem1->pNext, elem2 = elem2->pNext)
    {
        if(!list1->compareFunc(elem1->pValue, elem2->pValue)){
            return FALSE;
        }
    }
    // Make sure both lists reached their ends
    return (elem1 == NULL && elem2 == NULL);
}

void ListPrint(const PList list){
    // no NULL ptr
    if(list == NULL){
        return;
    }
    PNode elem;
    // print each element
    for (elem = list->head; elem != NULL; elem = elem->pNext)
    {
        list->printFunc(elem->pValue);
    }
    printf("\n");
}

int ListGetSize(const PList list){
    return list->size;
}
