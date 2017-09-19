/*
 * flight.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "flight.h"

pFLIGHT createFlight(int flightNum, FlightType flightType, char flightDest[], BOOL emergencyFlight)
{
	if (!validateFlightNum(flightNum))
		return NULL;
	if ((flightType != DOMESTIC) && (flightType != INTERNATIONAL))
		return NULL;
	if (!validateDestination(flightDest))
		return NULL;

	pFLIGHT p_flight = (pFLIGHT)malloc(sizeof(FLIGHT));
	if (NULL == p_flight)
		return NULL;

	p_flight->flightNum = flightNum;
	p_flight->flightType = flightType;
	strcpy(p_flight->flightDest, flightDest);
	p_flight->emergencyFlight = emergencyFlight;
	return p_flight;
}

void destroyFlight(pFLIGHT p_flight)
{
	if (NULL != p_flight)
		free(p_flight);
}


void printFlight(pFLIGHT p_flight)
{
	if (NULL == p_flight)
		return;

	char flightTypeCh;
	char emergencyFlightCh;

	if (p_flight->flightType == DOMESTIC)
		flightTypeCh = 'D';
	else
		flightTypeCh = 'I';

	if (p_flight->emergencyFlight == TRUE)
		emergencyFlightCh = 'E';
	else
		emergencyFlightCh = 'R';

	printf("Flight %d %c %s %c \n", p_flight->flightNum, flightTypeCh, p_flight->flightDest, emergencyFlightCh);
}


pFLIGHT cloneFlight(pFLIGHT p_flight)
{
	return createFlight(p_flight->flightNum, p_flight->flightType, p_flight->flightDest, p_flight->emergencyFlight);
}


BOOL isCapitalLetter(char c){
	return ((c >= 'A') && (c <= 'Z')); // TRUE for CAPS only
}


BOOL validateDestination(char* dest){
	if (3 != strlen(dest)){ // invalid length
		return FALSE;
	}
	int i;
	for (i = 0; i < 3; ++i){ // validate each character to be CAP
		if (!isCapitalLetter(dest[i]))
			return FALSE;
	}
	return TRUE;
}


BOOL validateFlightNum(int flightNum)
{
	if ((flightNum < 1) || (flightNum > MAX_ID)) // Illegal flight number
		return FALSE;
	return TRUE;
}











