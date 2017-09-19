#ifndef _PERSON_H_
#define _PERSON_H_

#include "defs.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Person_{
    char* name;
    int age, ID;
} Person,*PPerson;

//////////////////////////////////////////////////////////////////////////////////
// function name : PersonCreate                                                //
// description   : creates a Person with the input properties                 //
// parameters    : char* - Person's name                                     //
//                 int   - Person's age                                     //
//                 int   - Person's ID                                     //
// retrun value  : returns a pointer to the created Person, NULL if fails //
///////////////////////////////////////////////////////////////////////////
PPerson PersonCreate(const char*, const int, const int);
///////////////////////////////////////////////////////////////////////
// function name : printPerson                                      //
// description   : Person's print function (for a List ADT)        //
// parameters    : PElement - the Person to print (needs casting) //
// retrun value  : none                                          //
//////////////////////////////////////////////////////////////////
void printPerson(const PElement);

///////////////////////////////////////////////////////////////////////
// function name : clonePerson                                      //
// description   : Person's clone function (for a List ADT)        //
// parameters    : PElement - the Person to clone (needs casting) //
// retrun value  : pointer to the cloned Person (after casting)  //
//////////////////////////////////////////////////////////////////
PElement clonePerson(const PElement);
//////////////////////////////////////////////////////////////////////
// function name : destroyPerson                                   //
// description   : Person's freeing function (for a List ADT)     //
// parameters    : PElement - the Person to free (needs casting) //
// retrun value  : none                                         //
/////////////////////////////////////////////////////////////////
void destroyPerson(const PElement);
//////////////////////////////////////////////////////////////////////////
// function name : comparePerson                                       //
// description   : Person's compare function (for a List ADT)         //
// parameters    : PElement - 1st Person to compare (needs casting)  //
//                 PElement - 2nd Person to compare (needs casting) //
// retrun value  : TRUE if Persons match (same ID)                 //
////////////////////////////////////////////////////////////////////
BOOL comparePersons(const PElement, const PElement);

#endif
