/*busstops.h*/

//
// A collection of bus stops on the NU campus map.
//

#pragma once

#include <string>
#include <vector>

#include "busstop.h"

class BusStops
{
    private:
        vector<BusStop> mapBusStops;
    
    public:
        //
        // readMapBusStops
        //
        // Given a CSV file, reads through the document and 
        // stores all the bus stops into the given vector.
        //
        void readMapBusStops(string& filename);

        //
        // printAll
        //
        // prints all bus stops stored.
        //
        void printAll();

        //
        // getClosestBusStop
        //
        // Given a location, prints the closest Southbound and Northbound stops and the distance
        //
        void getClosestBusStop(pair<double, double> location, CURL* curl);

        //
        // predictBusArrival
        //
        // use the CTA API to fetch predicted bus arrival times for the closest bus stops
        //
        void predictBusArrival(BusStop& busstop, CURL* curl, string& response);

        //
        // accessors
        //
        int getNumBusStops();
};