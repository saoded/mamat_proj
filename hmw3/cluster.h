#ifndef _CLUSTER_H_
#define _CLUSTER_H_

#include "point.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Cluster_
{
    int dim;
    PList points;
} Cluster;

typedef Cluster* PCluster;

/////////////////////////////////////////////////////////////////////////////////
// function name : ClusterCreate                                              //
// description   : creates a Cluster with the input properties               //
// parameters    : int - Cluster's dimension                                //
// retrun value  : returns a pointer to the created Cluster, NULL if fails //
////////////////////////////////////////////////////////////////////////////
PCluster ClusterCreate(const int);
///////////////////////////////////////////////////////
// function name : PointDestroy                     //
// description   : free Cluster and its Points     //
// parameters    : PCluster - the Cluster to free //
// retrun value  : none                          //
//////////////////////////////////////////////////
void ClusterDestroy(PCluster);
//////////////////////////////////////////////////////////////////////////
// function name : ClusterAddPoint                                     //
// description   : adds a copy of input int to a Cluster's Point List //
// parameters    : PCluster - the Cluster to which we add            //
//                 PPoint   - the added Point                       //
// retrun value  : SUCCESS if added successfully, FAIL otherwise   //
////////////////////////////////////////////////////////////////////
Result ClusterAddPoint(PCluster, const PPoint);
///////////////////////////////////////////////////////////////////////////////////
// function name : ClusterGetMinDistance                                        //
// description   : find the distace from a Cluster to a Points                 //
// parameters    : PCluster - the Cluster                                     //
//                 PPoint   - the Point                                      //
// retrun value  : distance between input Point to closest Point in Cluster //
/////////////////////////////////////////////////////////////////////////////
int ClusterGetMinDistance(const PCluster, const PPoint);
////////////////////////////////////////////////////////////////////////////
// function name : ClusterGetMinDistanceWithin                           //
// description   : find the minimal distace between 2 Points in Cluster //
// parameters    : PCluster - the Cluster                              //
// retrun value  : distance between closest Points in Cluster         //
///////////////////////////////////////////////////////////////////////
int ClusterGetMinDistanceWithin(const PCluster);
////////////////////////////////////////////////////////
// function name : ClusterPrint                      //
// description   : print a Cluster and its Points   //
// parameters    : PCluster - the Cluster to print //
// retrun value  : none                           //
///////////////////////////////////////////////////
void ClusterPrint(const PCluster);

#endif