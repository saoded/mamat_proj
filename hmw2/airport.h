/*
 * airport.h
 */

#ifndef AIRPORT_H_
#define AIRPORT_H_

#include "runway.h"

typedef struct _RUNWAY_LIST_ELEM
{
	pRUNWAY p_runway;
	struct _RUNWAY_LIST_ELEM* pNext_runway;
} RUNWAY_LIST_ELEM;

/* Interface functions */
Result addRunway(int /*runwayNum*/, RunwayType /*runwayType*/);
Result removeRunway(int /*runwayNum*/);
Result addFlightToAirport(int /*flightNum*/, FlightType /*flightType*/, char[3] /*flightDest*/, BOOL /*emergencyFlight*/);
Result departFromRunway(int /*runwayNum*/, int /*numFlights*/);
Result changeDest(char[3] /*flightDestOrig*/, char[3] /*flightDestNew*/);
Result delay(char[3] /*flightDest*/); // TODO
void printAirport();
void destroyAirport();
BOOL isRunwayInList(int runwayNum);

#endif /* AIRPORT_H_ */
