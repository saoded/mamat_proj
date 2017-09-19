#ifndef _POINT_H_
#define _POINT_H_

#include "list.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct Point_{
    int dim;
    PList coordinates;
} Point;
typedef Point* PPoint;

///////////////////////////////////////////////////////////////////////////////
// function name : PointCreate                                              //
// description   : creates a Point with the input properties               //
// parameters    : int - Point's dimension                                //
// retrun value  : returns a pointer to the created Point, NULL if fails //
//////////////////////////////////////////////////////////////////////////
PPoint PointCreate(const int);
//////////////////////////////////////////////////////////////////////
// function name : PointClone                                      //
// description   : Point's clone function (for a List ADT)        //
// parameters    : PElement - the Point to clone (needs casting) //
// retrun value  : pointer to the cloned Point (after casting)  //
/////////////////////////////////////////////////////////////////
PElement PointClone(const PElement);
/////////////////////////////////////////////////////////////////////
// function name : PointDestroy                                   //
// description   : Point's freeing function (for a List ADT)     //
// parameters    : PElement - the Point to free (needs casting) //
// retrun value  : none                                        //
////////////////////////////////////////////////////////////////
void PointDestroy(const PElement);
/////////////////////////////////////////////////////////////////////////////
// function name : PointAddCoordinate                                     //
// description   : adds a copy of input int to a Point's coordinate List //
// parameters    : PPoint - the Point to which we add                   //
//                 int    - the added coordinate                       //
// retrun value  : SUCCESS if added successfully, FAIL otherwise      //
///////////////////////////////////////////////////////////////////////
Result PointAddCoordinate(PPoint, const int);
///////////////////////////////////////////////////////////////////////////////////////////////////////////
// function name : PointGetFirstCoordiante                                                              //
// description   : bring Point's coordinate List iterator to the beginning and return first coordinate //
// parameters    : PPoint - the Point we operate with                                                 //
// retrun value  : a pointer to the first coordinate in the list                                     //
//////////////////////////////////////////////////////////////////////////////////////////////////////
int PointGetFirstCoordiante(PPoint);
//////////////////////////////////////////////////////////////////////////////////////////
// function name : PointGetNextCoordiante                                              //
// description   : promote Point's coordinate List iterator and return its coordinate //
// parameters    : PPoint - the Point we operate with                                //
// retrun value  : a pointer to the next coordinate in the list                     //
/////////////////////////////////////////////////////////////////////////////////////
int PointGetNextCoordiante(PPoint);
//////////////////////////////////////////////////////////////////////
// function name : PointPrint                                      //
// description   : Point's print function (for a List ADT)        //
// parameters    : PElement - the Point to print (needs casting) //
// retrun value  : none                                         //
/////////////////////////////////////////////////////////////////
void PointPrint(const PElement);
/////////////////////////////////////////////////////////
// function name : GetPointDistance                   //
// description   : find the distace between 2 Points //
// parameters    : PPoint - 1st Point               //
//                 PPoint - 2nd Point              //
// retrun value  : distance between Points        //
///////////////////////////////////////////////////
int GetPointDistance(const PPoint, const PPoint);
/////////////////////////////////////////////////////////////////////////
// function name : PointCompare                                       //
// description   : Point's compare function (for a List ADT)         //
// parameters    : PElement - 1st Point to compare (needs casting)  //
//                 PElement - 2nd Point to compare (needs casting) //
// retrun value  : TRUE if Points match (same coordinates)        //
///////////////////////////////////////////////////////////////////
BOOL PointCompare(const PElement, const PElement);

//////////////////////////////////////////////////////////////////////
// function name : CoordinateCreate                                //
// description   : creates a coordinate with the input properties //
// parameters    : int - coordinate's value                      //
// retrun value  : returns a pointer to the created coordinate  //
/////////////////////////////////////////////////////////////////
int* CoordinateCreate(const int);
///////////////////////////////////////////////////////////////////////////
// function name : CoordinateClone                                      //
// description   : coordinate's clone function (for a List ADT)        //
// parameters    : PElement - the coordinate to clone (needs casting) //
// retrun value  : pointer to the cloned coordinate (after casting)  //
//////////////////////////////////////////////////////////////////////
PElement CoordinateClone(const PElement);
//////////////////////////////////////////////////////////////////////////
// function name : CoordinateDestroy                                   //
// description   : coordinate's freeing function (for a List ADT)     //
// parameters    : PElement - the coordinate to free (needs casting) //
// retrun value  : none                                             //
/////////////////////////////////////////////////////////////////////
void CoordinateDestroy(PElement);
/////////////////////////////////////////////////////////////
// function name : GetCoordinateDistance                  //
// description   : compute distace between 2 coordinates //
// parameters    : int* - 1st Point                     //
//                 int* - 2nd Point                    //
// retrun value  : distance between coordinates       //
///////////////////////////////////////////////////////
int GetCoordinateDistance(const int*, const int*);
//////////////////////////////////////////////////////////////////////////////
// function name : CoodinateCompare                                        //
// description   : coordinate's compare function (for a List ADT)         //
// parameters    : PElement - 1st coordinate to compare (needs casting)  //
//                 PElement - 2nd coordinate to compare (needs casting) //
// retrun value  : TRUE if coordinates match (0 distance)              //
////////////////////////////////////////////////////////////////////////
BOOL CoodinateCompare(const PElement, const PElement);
///////////////////////////////////////////////////////////////////////////
// function name : CoodinatePrint                                       //
// description   : coordinate's print function (for a List ADT)        //
// parameters    : PElement - the coordinate to print (needs casting) //
// retrun value  : none                                              //
//////////////////////////////////////////////////////////////////////
void CoodinatePrint(const PElement);

#endif