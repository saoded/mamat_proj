#include "cluster.h"

PCluster ClusterCreate(const int dim){
    // allocate Cluster
    PCluster newCluster = (PCluster)malloc(sizeof(Cluster));
    if(newCluster == NULL){
        return NULL;
    }
    // allocate Point List ADT
    newCluster->points = ListCreate(PointClone, PointDestroy, PointCompare, PointPrint);
    if(newCluster->points == NULL){
        free(newCluster);
        return NULL;
    }
    // assign parameters
    newCluster->dim = dim;
    return newCluster;
}

void ClusterDestroy(PCluster c){
    // no NULL ptr
    if(c == NULL){
        return;
    }
    // free Point List & Cluster
    ListDestroy(c->points);
    free(c);
}

Result ClusterAddPoint(PCluster c, const PPoint p){
    // No NULL objects, Point's dim must be right, and its coordinate list must be full;
    // Also, don't allow adding points that already exist.
    if(c == NULL || p == NULL || p->dim != c->dim || ListGetSize(p->coordinates) != p->dim || ListFind(p->coordinates, p) != NULL){
        return FAIL;
    }
    return ListAdd(c->points, p);
}

int ClusterGetMinDistance(const PCluster c, const PPoint p){
    PPoint piter;
    int distance = INT_MAX;
    int diter;
    for(piter = ListGetFirst(c->points); piter != NULL; piter = ListGetNext(c->points)){
        // if Point is in Cluster, just skip when you reach it..
        // It messes the heck out of the iterator
        if(p == piter){
            continue;
        }
        // take minimal distance possible
        diter = GetPointDistance(p, piter);
        if(distance > diter){
            distance = diter;
        }
    }
    return distance;
}

// NOTE: A PNode must be used here rather than PPoint.
// It's dirtier but we cannot ListGetFirst & ListGetNext,
// since this function calls ClusterGetMinDistance which uses them.
int ClusterGetMinDistanceWithin(const PCluster c){
    // no NULL ptr
    if(c == NULL){
        return 0;
    }
    int minDistance = INT_MAX;
    PNode n;
    int d;
    // take minimal distance btwn any 2 Points in Cluster
    for(n = c->points->head; n != NULL; n = n->pNext){
        d = ClusterGetMinDistance(c, (PPoint)(n->pValue));
        if(minDistance > d){
            minDistance = d;
        }
    }
    return minDistance;
}

void ClusterPrint(const PCluster c){
    // no NULL ptr
    if(c == NULL){
        return;
    }
    // print Cluster data
    printf("Cluster's dimension: %d\n", c->dim);
    // print Point List data
    ListPrint(c->points);
    // print minimal distance within Cluster
    printf("Minimum Square Distance: %d\n", ClusterGetMinDistanceWithin(c));
}