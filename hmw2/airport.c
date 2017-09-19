/*
 * airport.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "airport.h"

/* Globals */
static RUNWAY_LIST_ELEM* g_ListRunways = NULL;

Result addRunway(int runwayNum, RunwayType runwayType)
{
	if (isRunwayInList(runwayNum))
		return FAILURE;

	pRUNWAY p_runway = crateRunway(runwayNum, runwayType);
	if (NULL == p_runway)
		return FAILURE;

	RUNWAY_LIST_ELEM* p_runway_elem = g_ListRunways;
	RUNWAY_LIST_ELEM* p_runway_elem_add = (RUNWAY_LIST_ELEM*)malloc(sizeof(RUNWAY_LIST_ELEM));

	if (NULL == p_runway_elem_add)
		return FAILURE;

	p_runway_elem_add->p_runway = p_runway;
	p_runway_elem_add->pNext_runway = NULL;

	if (NULL == g_ListRunways)
	{
		g_ListRunways = p_runway_elem_add;
		return SUCCESS;
	}

	// list not empty
	while (NULL != p_runway_elem->pNext_runway)
	{
		p_runway_elem = p_runway_elem->pNext_runway;
	}

	p_runway_elem->pNext_runway = p_runway_elem_add;
	return SUCCESS;
}


Result removeRunway(int runwayNum)
{
	RUNWAY_LIST_ELEM* p_runway_elem = g_ListRunways;
	RUNWAY_LIST_ELEM* p_runway_elem_tmp = NULL; // hold previous runway

	while ((NULL != p_runway_elem) && (p_runway_elem->p_runway->runwayNum != runwayNum))
	{
		p_runway_elem_tmp = p_runway_elem;
		p_runway_elem = p_runway_elem->pNext_runway;
	}
	if (NULL == p_runway_elem) // not found runway
		return FAILURE;

	// remove all flights in runway, remove runway
	destroyRunway(p_runway_elem->p_runway); // all flights in runway removed

	if (NULL != p_runway_elem_tmp) // previous runway exists
		p_runway_elem_tmp->pNext_runway = p_runway_elem->pNext_runway; // remove runway from list
	else // remove first runway from list
		g_ListRunways = p_runway_elem->pNext_runway;

	free(p_runway_elem);
	return SUCCESS;
}


Result addFlightToAirport(int flightNum, FlightType flightType, char flightDest[], BOOL emergencyFlight)
{
	RUNWAY_LIST_ELEM* p_runway_elem = g_ListRunways;
	if (NULL == p_runway_elem) // No runways
		return FAILURE;

	pFLIGHT p_flight = createFlight(flightNum, flightType, flightDest, emergencyFlight);
	if (NULL == p_flight)
		return FAILURE;

	RUNWAY_LIST_ELEM* p_runway_elem_add = NULL;
	int numFlightsRunway;
	int minNumFlights = MAX_ID + 1; // Init
	int minRunwayNum = MAX_ID + 1; // Init

	// Scan all runways for (flightType) and assign flight to the one where current number of flights is
	// minimal (or lowest index runway if some runways have same number of flights).
	while (NULL != p_runway_elem)
	{
		// If flight number already exists, report failure
		if (isFlightExists(p_runway_elem->p_runway, flightNum))
		{
			destroyFlight(p_flight);
			return FAILURE;
		}

		if (p_runway_elem->p_runway->runwayType == flightType)
		{
			numFlightsRunway = getFlightNum(p_runway_elem->p_runway);
			if ((numFlightsRunway < minNumFlights) ||
					((numFlightsRunway == minNumFlights) && (p_runway_elem->p_runway->runwayNum < minRunwayNum)))
			{
				p_runway_elem_add = p_runway_elem;
				minNumFlights = numFlightsRunway;
				minRunwayNum = p_runway_elem->p_runway->runwayNum;
			}
		}
		p_runway_elem = p_runway_elem->pNext_runway;
	}
	if (MAX_ID + 1 == minRunwayNum) // not found suitable runway to add flight
	{
		destroyFlight(p_flight);
		return FAILURE;
	}

	addFlight(p_runway_elem_add->p_runway, p_flight);
	destroyFlight(p_flight); // addFlight clones p_flight data, free memory
	return SUCCESS;
}


Result departFromRunway(int runwayNum, int numFlights)
{
	if (0 == numFlights)
		return FAILURE;

	RUNWAY_LIST_ELEM* p_runway_elem = g_ListRunways;
	if (NULL == p_runway_elem)
		return FAILURE;

	while ((NULL != p_runway_elem) && (p_runway_elem->p_runway->runwayNum != runwayNum))
		p_runway_elem = p_runway_elem->pNext_runway;
	if (NULL == p_runway_elem)
		return FAILURE;

	int numFlightsRunway = getFlightNum(p_runway_elem->p_runway);
	int i;
	if (numFlightsRunway >= numFlights)
	{
		FLIGHT_LIST_ELEM* flightsList_tmp;
		// remove (numFlights) first flights in list
		for (i=0; i<numFlights; i++)
		{
			destroyFlight(p_runway_elem->p_runway->flightList->p_flight);
			flightsList_tmp = p_runway_elem->p_runway->flightList;
			p_runway_elem->p_runway->flightList = p_runway_elem->p_runway->flightList->pNext_flight;
			free(flightsList_tmp);
		}
		return SUCCESS;
	}
	else
		return FAILURE;
}


Result changeDest(char flightDestOrig[], char flightDestNew[])
{
	if ((!validateDestination(flightDestOrig)) || (!validateDestination(flightDestNew)))
		return FAILURE;

	RUNWAY_LIST_ELEM* p_runway_elem = g_ListRunways;
	FLIGHT_LIST_ELEM* flightsListRunway;
	while (NULL != p_runway_elem)
	{
		flightsListRunway = p_runway_elem->p_runway->flightList;
		while (NULL != flightsListRunway)
		{
			if (0 == strcmp(flightsListRunway->p_flight->flightDest, flightDestOrig)) // found flight with original destination
				strcpy(flightsListRunway->p_flight->flightDest, flightDestNew);
			flightsListRunway = flightsListRunway->pNext_flight;
		}
		p_runway_elem = p_runway_elem->pNext_runway;
	}
	return SUCCESS;
}


Result delay(char flightDest[])
{
	if (FALSE == validateDestination(flightDest))
		return FAILURE;

	RUNWAY_LIST_ELEM* p_runway_elem = g_ListRunways;
	FLIGHT_LIST_ELEM* flightsListRunway;
	pFLIGHT p_flight_tmp;
	int flightNum_tmp;

	while (NULL != p_runway_elem)
	{
		BOOL flightsRunwayNotRemoved[MAX_ID] = {FALSE};
		getFlightsListRunway(p_runway_elem->p_runway, flightsRunwayNotRemoved);
		flightsListRunway = p_runway_elem->p_runway->flightList;
		while (NULL != flightsListRunway)
		{
			if (0 == strcmp(flightsListRunway->p_flight->flightDest, flightDest))
			{
				flightNum_tmp = flightsListRunway->p_flight->flightNum;

				// Verify that this list has not already been removed and added back to the list
				if (TRUE == flightsRunwayNotRemoved[flightNum_tmp-1]) // Not yet removed, remove and add it back
				{
					p_flight_tmp = cloneFlight(flightsListRunway->p_flight); // clone flight which is to be removed
					if (FAILURE == removeFlight(p_runway_elem->p_runway, flightNum_tmp)) // remove flight from runway flights list
						return FAILURE;
					else
						flightsListRunway = p_runway_elem->p_runway->flightList; // Update flight list pointer

					if (FAILURE == addFlight(p_runway_elem->p_runway, p_flight_tmp)) // add flight back to the list (according to priority rules)
					{
						destroyFlight(p_flight_tmp);
						return FAILURE;
					}
					else
						flightsListRunway = p_runway_elem->p_runway->flightList; // Update flight list pointer

					flightsRunwayNotRemoved[flightNum_tmp-1] = FALSE; // Mark it as removed already
					destroyFlight(p_flight_tmp);
					//printAirport();
				}
				else
					flightsListRunway = flightsListRunway->pNext_flight;
			}
			else
				flightsListRunway = flightsListRunway->pNext_flight;
		}
		p_runway_elem = p_runway_elem->pNext_runway;
	}
	return SUCCESS;
}


void printAirport()
{
	RUNWAY_LIST_ELEM* p_runway_elem = g_ListRunways;
	printf("Airport status:\n");
	while (NULL != p_runway_elem)
	{
		printRunway(p_runway_elem->p_runway);
		p_runway_elem = p_runway_elem->pNext_runway;
	}
	printf("\n");
}


void destroyAirport()
{
	if (NULL == g_ListRunways)
		return;

	RUNWAY_LIST_ELEM* p_runway_elem = g_ListRunways;
	while (NULL != g_ListRunways)
	{
		p_runway_elem = g_ListRunways;
		destroyRunway(g_ListRunways->p_runway);
		g_ListRunways = g_ListRunways->pNext_runway;
		free(p_runway_elem);
	}
}


BOOL isRunwayInList(int runwayNum)
{
	if (!validateRunwayNum(runwayNum))
		return FALSE;

	RUNWAY_LIST_ELEM* p_runway_elem;
	for (p_runway_elem = g_ListRunways; p_runway_elem != NULL; p_runway_elem = p_runway_elem->pNext_runway)
		if (p_runway_elem->p_runway->runwayNum == runwayNum)
			return TRUE;
	return FALSE;
}

















