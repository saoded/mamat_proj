#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "airport.h"

#define MAX_LINE_SIZE 255

unsigned short parseUShort(char* str){
	int resInt = atoi(str);
	if (resInt < 0 || resInt > USHRT_MAX){
		return 0;
	}
	return (unsigned short)resInt;
}

BOOL tryParseFlightType(char* str){
	if(strlen(str) == 1 && ((*str == 'D') || (*str == 'I'))){
    	return TRUE;
    }
    return FALSE;
}

BOOL tryParseEmergency(char* str){
	if(strlen(str) == 1 && ((*str == 'E') || (*str == 'R'))){
    	return TRUE;
    }
    return FALSE;
}

int main() {

    char szLine[MAX_LINE_SIZE];
  	char* delimiters = " \t\n";
  	char* pszCommand;

  	while (fgets(szLine, MAX_LINE_SIZE, stdin)) {
    	pszCommand = strtok(szLine, delimiters);
    	// Empty case
    	if(pszCommand == NULL) continue;
    	// Exit case
    	if(strcmp(pszCommand, "Exit") == 0){
	    	destroyAirport();
    		break;
    	}
    	// Print case
    	if(strcmp(pszCommand, "Print") == 0){
	    	printAirport();
    		continue;
    	}
    	// Insert case
    	if(strcmp(pszCommand, "Insert") == 0){
	    	char* pszRunwayId = strtok(NULL, delimiters);
    		char* pszRunwayType = strtok(NULL, delimiters);
	    	// validate existence
    		if(pszRunwayId == NULL || pszRunwayType == NULL){
	    		fprintf(stderr, "Insert failed: not enough parameters.\n");
    			continue;
    		}
    		// Handle 1st arg:
    		// 1st arg must be ushort
    		unsigned short runwayId = parseUShort(pszRunwayId);
    		if(runwayId == 0 && strcmp(pszRunwayId, "0")!=0){
	    		fprintf(stderr, "Insert execution failed\n");
    			continue;
    		}

 			// Handle 2nd arg:
    		// 2nd arg must be a 'I' or 'D'
    		if(!tryParseFlightType(pszRunwayType)){
	    		fprintf(stderr, "Insert execution failed\n");
    			continue;
    		}
    		RunwayType runwayType = (*pszRunwayType == 'D')?(DOMESTIC):(INTERNATIONAL);

    		// Execute Command
    		Result res = addRunway(runwayId, runwayType);
    		if(res == FAILURE) fprintf(stderr, "Insert execution failed (but parse ok)\n");
    		continue;
    	}
    	// Remove case
    	if(strcmp(pszCommand, "Remove") == 0){
	    	char* pszRunwayId = strtok(NULL, delimiters);
    		// validate existence
    		if(pszRunwayId == NULL){
	    		fprintf(stderr, "Remove failed: not enough parameters.\n");
    			continue;
    		}
    		// Handle 1st arg:
    		// 1st arg must be ushort
    		unsigned short runwayId = parseUShort(pszRunwayId);
    		if(runwayId == 0 && strcmp(pszRunwayId, "0")!=0){
	    		fprintf(stderr, "Remove execution failed\n");
    			continue;
    		}

    		// Execute Command
    		Result res = removeRunway(runwayId);
    		if(res == FAILURE) fprintf(stderr, "Remove execution failed (but parse ok)\n");
    		continue;
    	}
    	// Add case
    	if(strcmp(pszCommand, "Add") == 0){
	    	char* pszFlightId = strtok(NULL, delimiters);
    		char* pszFlightType = strtok(NULL, delimiters);
    		char* pszFlightDest = strtok(NULL, delimiters);
    		char* pszFlightEmergency = strtok(NULL, delimiters);
	    	// validate existence
    		if(pszFlightId == NULL || pszFlightType == NULL || pszFlightDest == NULL || pszFlightEmergency == NULL){
	    		fprintf(stderr, "Add failed: not enough parameters.\n");
    			continue;
    		}
    		// Handle 1st arg:
    		unsigned short flightId = parseUShort(pszFlightId);
    		// 1st arg must be ushort
    		if(flightId == 0 && strcmp(pszFlightId, "0")!=0){
	    		fprintf(stderr, "Add execution failed (Id)\n");
    			continue;
    		}

 			// Handle 2nd arg:
    		// 2nd arg must be a 'I' or 'D'
    		if(!tryParseFlightType(pszFlightType)){
	    		fprintf(stderr, "Add execution failed (type)\n");
    			continue;
    		}
    		FlightType flightType = (*pszFlightType == 'D')?(DOMESTIC):(INTERNATIONAL);

			// Handle 3rd arg:
    		// 3rd arg must be an array of 3 chars
    		if(!validateDestination(pszFlightDest)){
	    		fprintf(stderr, "Add execution failed (destination)\n");
    			continue;
    		}

    		// Handle 4th arg:
    		// 4th arg must be a 'E' or 'R'
    		if(!tryParseEmergency(pszFlightEmergency)){
	    		fprintf(stderr, "Add execution failed (emergency)\n");
    			continue;
    		}
    		BOOL isEmerg = (*pszFlightEmergency == 'E')?(TRUE):(FALSE);

    		// Execute Command
    		Result res = addFlightToAirport(flightId, flightType, pszFlightDest, isEmerg);
    		if(res == FAILURE) fprintf(stderr, "Add execution failed (but parse ok)\n");
    		continue;
    	}
    	// Depart case
    	if(strcmp(pszCommand, "Depart") == 0){
	    	char* pszRunwayId = strtok(NULL, delimiters);
	    	char* pszNumOfFlights = strtok(NULL, delimiters);
    		// validate existence
    		if(pszRunwayId == NULL || pszNumOfFlights == NULL){
	    		fprintf(stderr, "Depart failed: not enough parameters.\n");
    			continue;
    		}
    		// Handle 1st arg:
    		// 1st arg must be ushort
    		unsigned short runwayId = parseUShort(pszRunwayId);
    		if(runwayId == 0 && strcmp(pszRunwayId, "0")!=0){
	    		fprintf(stderr, "Depart execution failed\n");
    			continue;
    		}

    		// Handle 2nd arg:
    		// 2nd arg must be ushort
    		unsigned short numOfFlights = parseUShort(pszNumOfFlights);
    		if(numOfFlights == 0 && strcmp(pszNumOfFlights, "0")!=0){
	    		fprintf(stderr, "Depart execution failed\n");
    			continue;
    		}

    		// Execute Command
    		Result res = departFromRunway(runwayId, numOfFlights);
    		if(res == FAILURE) fprintf(stderr, "Depart execution failed (but parse ok)\n");
    		continue;
    	}
    	// Change case
    	if(strcmp(pszCommand, "Change") == 0){
    		char* pszOldDest = strtok(NULL, delimiters);
    		char* pszNewDest = strtok(NULL, delimiters);
	    	// validate existence
    		if(pszOldDest == NULL || pszNewDest == NULL){
	    		fprintf(stderr, "Change failed: not enough parameters.\n");
    			continue;
    		}
			// Handle 1st arg:
    		// 1st arg must be an array of 3 chars
    		if(!validateDestination(pszOldDest)){
	    		fprintf(stderr, "Change execution failed (destination)\n");
    			continue;
    		}

    		// Handle 2nd arg:
    		// 2nd arg must be an array of 3 chars
    		if(!validateDestination(pszNewDest)){
	    		fprintf(stderr, "Change execution failed (destination)\n");
    			continue;
    		}

    		// Execute Command
    		Result res = changeDest(pszOldDest, pszNewDest);
    		if(res == FAILURE) fprintf(stderr, "Change execution failed (but parse ok)\n");
    		continue;
    	}
    	// Delay case
    	if(strcmp(pszCommand, "Delay") == 0){
    		char* pszDelayedDest = strtok(NULL, delimiters);
	    	// validate existence
    		if(pszDelayedDest == NULL){
	    		fprintf(stderr, "Delay failed: not enough parameters.\n");
    			continue;
    		}
			// Handle 1st arg:
    		// 1st arg must be an array of 3 chars
    		if(!validateDestination(pszDelayedDest)){
	    		fprintf(stderr, "Delay execution failed (destination)\n");
    			continue;
    		}

    		// Execute Command
    		Result res = delay(pszDelayedDest);
    		if(res == FAILURE) fprintf(stderr, "Delay execution failed (but parse ok)\n");
    		continue;
    	}

		fprintf(stderr, "Command not found\n");
		continue;
  	}
  	return 0;
}
