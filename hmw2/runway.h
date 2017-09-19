/*
 * runway.h
 */

#ifndef RUNWAY_H_
#define RUNWAY_H_

#include "ex2.h"
#include "flight.h"

typedef FlightType RunwayType;

typedef struct _FLIGHT_LIST_ELEM
{
	pFLIGHT p_flight;
	struct _FLIGHT_LIST_ELEM* pNext_flight;
} FLIGHT_LIST_ELEM;

typedef struct _RUNWAY
{
	int runwayNum; // between 1 and MAX_ID
	RunwayType runwayType; // {‫‪DOMESTIC,‬‬ ‫‪INTERNATIONAL‬‬}
	FLIGHT_LIST_ELEM* flightList;
} RUNWAY;

typedef RUNWAY* pRUNWAY;

/* Interface functions */
pRUNWAY crateRunway(int /*runwayNum*/, RunwayType /*runwayType*/);
void destroyRunway(pRUNWAY /*p_runway*/);
void destroyFlightList(FLIGHT_LIST_ELEM* /*flightList*/);
BOOL isFlightExists(pRUNWAY /*p_runway*/, int /*flightNum*/);
int getFlightNum(pRUNWAY /*p_runway*/);
Result addFlight(pRUNWAY /*p_runway*/, pFLIGHT /*p_flight*/);
Result addEmergencyFlight(pRUNWAY /*p_runway*/, FLIGHT_LIST_ELEM* /*p_flight_elem*/);
Result addRegularFlight(pRUNWAY /*p_runway*/, FLIGHT_LIST_ELEM* /*p_flight_elem*/);
Result removeFlight(pRUNWAY /*p_runway*/, int /*flightNum*/);
Result depart(pRUNWAY /*p_runway*/);
void printRunway(pRUNWAY /*p_runway*/);

void getFlightsListRunway(pRUNWAY /*p_runway*/, BOOL[MAX_ID] /*flightsArrBool*/);
BOOL validateRunwayNum(int /*runwayNum*/);
BOOL validateRunwayType(RunwayType /*runwayType*/);

#endif /* RUNWAY_H_ */
