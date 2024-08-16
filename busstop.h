/*busstop.h*/

//
// A bus stop on the NU campus map.
//

#pragma once

#include <string>
#include <iostream>
#include <utility>

using namespace std;

//
// BusStop
//
// Defines a bus stop on campus.
// Consists of a stop ID, the bus route, the stop name, the direction of travel,
// the location of the stop, and the position in latitude and longitude.
class BusStop
{
    public:
        int StopID;
        int BusRoute;
        string StopName;
        string Direction;
        string LocationDesc;
        pair<double,double> Position;

    //
    // default constructor:
    //
    BusStop();

    //
    // constructor:
    //
    BusStop(int stopid, int busroute, string stopname, string direction, string locationdesc, pair<double,double> position);

    //
    // print
    //
    void print();

    //
    // accessors
    //

    // stop id
    int getStopID();

    // bus route
    int getBusRoute();

    // stop name
    string getStopName();

    // direction
    string getDirection();

    // location
    string getLocationDesc();

    // position (lat, lon)
    pair<double, double> getPosition();
};