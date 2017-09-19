/*
 * flight.h
 */

#ifndef FLIGHT_H_
#define FLIGHT_H_

#include "ex2.h"

typedef struct _FLIGHT
{
	int flightNum; // between 1 and MAX_ID
	FlightType flightType; // {‫‪DOMESTIC,‬‬ ‫‪INTERNATIONAL‬‬}
	char flightDest[3];
	BOOL emergencyFlight;
} FLIGHT;

typedef FLIGHT* pFLIGHT;

/* Interface functions */
pFLIGHT createFlight(int /*flightNum*/, FlightType /*flightType*/, char[3] /*flightDest*/, BOOL /*emergencyFlight*/);
void destroyFlight(pFLIGHT /*p_flight*/);
void printFlight(pFLIGHT /*p_flight*/);
pFLIGHT cloneFlight(pFLIGHT /*p_flight*/);
BOOL validateFlightNum(int /*flightNum*/);

//////////////////////////////////////////////////////////////////////////////////////
// function name : validateDestination                                              //
// description   : checks if a char array contains only & exactly 3 capital letters //
// parameters    : char* - the char array to check                                  //
// retrun value  : TRUE  - the input is 3 capital letters                           //
//				   FALSE - the input is not 3 capital letters                       //
//////////////////////////////////////////////////////////////////////////////////////
BOOL validateDestination(char*);

#endif /* FLIGHT_H_ */
