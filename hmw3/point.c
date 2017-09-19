#include "point.h"

// Point need a List of Coordiantes (ints).
// let's first define some methods for those:

int* CoordinateCreate(const int val){
    // allocate
    int* newCoordinate = (int*)malloc(sizeof(int));
    if (newCoordinate == NULL){
        return NULL;
    }
    // assign
    *newCoordinate = val;
    return newCoordinate;
}

PElement CoordinateClone(const PElement coordinate){
    // clone
    return (PElement)CoordinateCreate(*((int*)coordinate));
}

void CoordinateDestroy(PElement coordinate){
    // free
    free((int*)coordinate);
}

int GetCoordinateDistance(const int* c1, const int* c2){
    // d = (c1 - c2)^2
    int coordinateDiff = *c1 - *c2;
    return (coordinateDiff * coordinateDiff);
}

BOOL CoodinateCompare(const PElement coordinate1, const PElement coordinate2){
    // return (*((int*)coordinate1) == *((int*)coordinate2));
    return GetCoordinateDistance((int*)coordinate1, (int*)coordinate2) == 0; // true if d == 0
}

void CoodinatePrint(const PElement coordinate){
    // print coordinate with space following
    printf("%d ", *((int*)coordinate));
}

// Now let's get to Point's functionality

PPoint PointCreate(const int dim){
    // allocate Point
    PPoint newPoint = (PPoint)malloc(sizeof(Point));
    if(newPoint == NULL){
        return NULL;
    }
    // create coordinate list
    newPoint->coordinates = ListCreate(CoordinateClone, CoordinateDestroy, CoodinateCompare, CoodinatePrint);
    if(newPoint->coordinates == NULL){
        free(newPoint);
        return NULL;
    }
    // assign
    newPoint->dim = dim;
    return newPoint;
}

PElement PointClone(const PElement point){
    // no NULL ptr
    if(point == NULL){
        return NULL;
    }
    // create the Point
    PPoint p = (PPoint)point;
    PPoint newPoint = PointCreate(p->dim);
    int* c;
    // copy the cooridinates
    for(c = (int*)ListGetFirst(p->coordinates); c != NULL; c = (int*)ListGetNext(p->coordinates)){
        ListAdd(newPoint->coordinates, (PElement)c);
    }
    return (PElement)newPoint;
}

void PointDestroy(PElement point){
    // no NULL ptr
    if(point == NULL){
        return;
    }
    PPoint p = (PPoint)point;
    // free coordinate List ADT
    ListDestroy(p->coordinates);
    // free Point
    free(p);
}

int GetPointDistance(const PPoint p1, const PPoint p2){
    // no ptrs to the same element (it messes with their iterator)
    if (p1 == p2){
        return 0;
    }
    int distance = 0;
    int* p1c = (int*)ListGetFirst(p1->coordinates);
    int* p2c = (int*)ListGetFirst(p2->coordinates);
    // sum up distace of each coordinate.
    // using 'while' bc 'for' line was too long.
    while (p1c != NULL /*&& p2c != NULL*/){ // p2c's size is necessarily the same as p1c's
        distance += GetCoordinateDistance(p1c, p2c);
        p1c = (int*)ListGetNext(p1->coordinates);
        p2c = (int*)ListGetNext(p2->coordinates);
    }
    return distance;
}

BOOL PointCompare(const PElement point1, const PElement point2){
    // no NULL ptrs
    if(point1 == NULL || point2 == NULL){
        return FALSE;
    }
    // casts
    PPoint p1 = (PPoint)point1;
    PPoint p2 = (PPoint)point2;
    // compare coordinates
    return ListCompare(p1->coordinates, p2->coordinates);
}

void PointPrint(const PElement point){
    // no NULL ptr
    if(point == NULL){
        return;
    }
    PPoint p = (PPoint)point;
    // print Point's data
    printf("Point Dimension: %d, Size: %d, Coordinates: ", p->dim, ListGetSize(p->coordinates));
    // print coordinates' data
    ListPrint(p->coordinates);
}

Result PointAddCoordinate(PPoint p, const int c){
    // no NULL ptr, no adding coordinate to full Point
    if(p == NULL || ListGetSize(p->coordinates) == p->dim){
        return FAIL;
    }
    return ListAdd(p->coordinates, (PElement)&c);
}

// 2 unused but required functions
// Y U NO return int*??

int PointGetFirstCoordiante(PPoint p){
    if(p == NULL || ListGetSize(p->coordinates) == 0){
        return 0;
    }
    int* firstCoordinate = ListGetFirst(p->coordinates);
    return ((firstCoordinate == NULL) ? 0 : *firstCoordinate);
}

int PointGetNextCoordiante(PPoint p){
    if(p == NULL || ListGetSize(p->coordinates) == 0){
        return 0;
    }
    int* nextCoordinate = ListGetNext(p->coordinates);
    return ((nextCoordinate == NULL) ? 0 : *nextCoordinate);
}