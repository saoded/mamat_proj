/*
 * runway.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "runway.h"

pRUNWAY crateRunway(int runwayNum, RunwayType runwayType)
{
	if ((!validateRunwayNum(runwayNum)) || (!validateRunwayType(runwayType)))
		return NULL;

	pRUNWAY p_runway = (pRUNWAY)malloc(sizeof(RUNWAY));
	if (NULL == p_runway)
		return NULL;

	p_runway->runwayNum = runwayNum;
	p_runway->runwayType = runwayType;
	p_runway->flightList = NULL; // Init flight list to NULL

	return p_runway;
}


void destroyRunway(pRUNWAY p_runway)
{
	if (NULL == p_runway)
		return;

	// Free all flights
	destroyFlightList(p_runway->flightList);
	free(p_runway);
}


void destroyFlightList(FLIGHT_LIST_ELEM* flightList)
{
	if (NULL == flightList)
		return;

	destroyFlightList(flightList->pNext_flight); // recursive call
	destroyFlight(flightList->p_flight);
	free(flightList);
}


BOOL isFlightExists(pRUNWAY p_runway, int flightNum)
{
	if (!validateFlightNum(flightNum)) // Illegal flight number
		return FALSE;

	// Scan runway flights to find flight
	FLIGHT_LIST_ELEM* p_flight_list_tmp = p_runway->flightList;
	while (NULL != p_flight_list_tmp)
	{
		if (p_flight_list_tmp->p_flight->flightNum == flightNum)
			return TRUE;
		p_flight_list_tmp = p_flight_list_tmp->pNext_flight;
	}
	return FALSE;
}


int getFlightNum(pRUNWAY p_runway)
{
	if (NULL == p_runway)
		return -1; // Illegal input

	int numFlights = 0;
	// Scan all runway flights to count them
	FLIGHT_LIST_ELEM* p_flight_list_tmp = p_runway->flightList;
	while ((NULL != p_flight_list_tmp))
	{
		numFlights++;
		p_flight_list_tmp = p_flight_list_tmp->pNext_flight;
	}
	return numFlights;
}


Result addFlight(pRUNWAY p_runway, pFLIGHT p_flight)
{
	if (NULL == p_runway || NULL == p_flight)
		return FAILURE;
	if (isFlightExists(p_runway, p_flight->flightNum)) // Flight number already in runway
		return FAILURE;
	if (p_runway->runwayType != p_flight->flightType) // flight type not matching runway type
		return FAILURE;

	FLIGHT_LIST_ELEM* p_flight_list_elem = (FLIGHT_LIST_ELEM*)malloc(sizeof(FLIGHT_LIST_ELEM));
	if (NULL == p_flight_list_elem)
		return FAILURE;

	p_flight_list_elem->p_flight = cloneFlight(p_flight); // clone input flight data to eliminate dependency on outer memory management
	if (NULL == p_flight_list_elem->p_flight)
	{
		free(p_flight_list_elem);
		return FAILURE;
	}
	p_flight_list_elem->pNext_flight = NULL;

	if (p_flight_list_elem->p_flight->emergencyFlight)
		return addEmergencyFlight(p_runway, p_flight_list_elem);
	else
		return addRegularFlight(p_runway, p_flight_list_elem);

	return SUCCESS;
}


Result addEmergencyFlight(pRUNWAY p_runway, FLIGHT_LIST_ELEM* p_flight_elem)
{
	if (NULL == p_runway)
		return FAILURE;

	// handle list without emergency flights (including empty)
	if ((NULL == p_runway->flightList) || (!p_runway->flightList->p_flight->emergencyFlight))
	{
		p_flight_elem->pNext_flight = p_runway->flightList;
		p_runway->flightList = p_flight_elem;
		return SUCCESS;
	}

	// List contains emergency flights. loop over flights list until non-emergency found (or end reached)
	FLIGHT_LIST_ELEM* p_flight_list_tmp;
	for (p_flight_list_tmp = p_runway->flightList; p_flight_list_tmp->pNext_flight != NULL; p_flight_list_tmp = p_flight_list_tmp->pNext_flight)
	{
		if (p_flight_list_tmp->pNext_flight->p_flight->emergencyFlight)
			continue;
		// add flight at end of emergency flights
		p_flight_elem->pNext_flight = p_flight_list_tmp->pNext_flight;
		p_flight_list_tmp->pNext_flight = p_flight_elem;
		return SUCCESS;
	}
	// list full of emergency flights, add at the end
	p_flight_list_tmp->pNext_flight = p_flight_elem;
	return SUCCESS;
}


Result addRegularFlight(pRUNWAY p_runway, FLIGHT_LIST_ELEM* p_flight_elem)
{
	if (NULL == p_runway)
		return FAILURE;

	if (NULL == p_runway->flightList)
	{
		p_runway->flightList = p_flight_elem;
		return SUCCESS;
	}
	// Add at the end of list
	FLIGHT_LIST_ELEM* p_flight_list_tmp;
	for (p_flight_list_tmp = p_runway->flightList; p_flight_list_tmp->pNext_flight != NULL; p_flight_list_tmp = p_flight_list_tmp->pNext_flight){}
	p_flight_list_tmp->pNext_flight = p_flight_elem; // add at the end
	return SUCCESS;
}


Result removeFlight(pRUNWAY p_runway, int flightNum)
{
	if ((NULL == p_runway) || (NULL == p_runway->flightList) || (!isFlightExists(p_runway, flightNum)))
		return FAILURE;

	FLIGHT_LIST_ELEM* p_flight_list_tmp = p_runway->flightList;

	// Remove flight if at beginning of list
	if (p_flight_list_tmp->p_flight->flightNum == flightNum)
	{
		p_runway->flightList = p_runway->flightList->pNext_flight;
		destroyFlight(p_flight_list_tmp->p_flight);
		free(p_flight_list_tmp);
		return SUCCESS;
	}

	// Scan runway flights to find this flight
	while (NULL != p_flight_list_tmp->pNext_flight)
	{
		if (p_flight_list_tmp->pNext_flight->p_flight->flightNum == flightNum)
		{
			FLIGHT_LIST_ELEM* p_flight_list_tmp2 = p_flight_list_tmp->pNext_flight;
			p_flight_list_tmp->pNext_flight = p_flight_list_tmp->pNext_flight->pNext_flight;
			destroyFlight(p_flight_list_tmp2->p_flight); // remove flight from memory
			free(p_flight_list_tmp2);
			return SUCCESS;
		}
		else
			p_flight_list_tmp = p_flight_list_tmp->pNext_flight;
	}
	return FAILURE;
}


Result depart(pRUNWAY p_runway)
{
	if (NULL == p_runway)
		return FAILURE;
	if (NULL == p_runway->flightList) // Empty flight list
		return FAILURE;

	return removeFlight(p_runway, p_runway->flightList->p_flight->flightNum); // remove first flight in list
}


void printRunway(pRUNWAY p_runway)
{
	if (NULL == p_runway)
	{
		printf("%d flights are waiting: \n", 0);
		return;
	}

	char runwayTypeStr[20];
	if (p_runway->runwayType == DOMESTIC)
		strcpy(runwayTypeStr, "domestic");
	else
		strcpy(runwayTypeStr, "international");
	printf("Runway %d %s \n", p_runway->runwayNum, runwayTypeStr);

	FLIGHT_LIST_ELEM* p_flight_list_tmp = p_runway->flightList;
	int numFlights = getFlightNum(p_runway);
	if (-1 == numFlights)
		return;
	printf("%d flights are waiting: \n", numFlights);

	while (NULL != p_flight_list_tmp)
	{
		printFlight(p_flight_list_tmp->p_flight);
		p_flight_list_tmp = p_flight_list_tmp->pNext_flight;
	}
}


void getFlightsListRunway(pRUNWAY p_runway, BOOL flightsListTF[])
{
	// Input flightsListTF is assumed init to FALSE
	FLIGHT_LIST_ELEM* p_flight_list = p_runway->flightList;
	while (NULL != p_flight_list)
	{
		flightsListTF[p_flight_list->p_flight->flightNum - 1] = TRUE; // flightNum in range [1, MAX_ID]
		p_flight_list = p_flight_list->pNext_flight;
	}
}


BOOL validateRunwayNum(int runwayNum)
{
	if ((runwayNum < 1) || (runwayNum > MAX_ID)) // Illegal runway number
		return FALSE;
	return TRUE;
}


BOOL validateRunwayType(RunwayType runwayType)
{
	if ((runwayType != DOMESTIC) && (runwayType != INTERNATIONAL))
		return FALSE;
	return TRUE;
}


