/*busstop.cpp*/

//
// A bus stop on the NU campus map.
//

#include <string>
#include <iostream>
#include <utility>

#include "busstop.h"

using namespace std;

//
// default constructor
//
BusStop::BusStop()
{}

//
// constructor
//
BusStop::BusStop(int stopid, int busroute, string stopname, string direction, string locationdesc, pair<double,double> position)
    :   StopID(stopid), BusRoute(busroute), StopName(stopname), Direction(direction), LocationDesc(locationdesc), Position(position)
{}

//
// print
//
void BusStop::print()
{
    cout << this->StopID << ": bus " << this->BusRoute
    << ", " << this->StopName << ", " << this->Direction
    << ", " << this->LocationDesc << ", location ("
    << this->Position.first << ", " << this->Position.second << ')' << endl;

    return;
}

//
// accessors
//

// stop id
int BusStop::getStopID() {
    return this->StopID;
}

// bus route
int BusStop::getBusRoute() {
    return this->BusRoute;
}

// stop name
string BusStop::getStopName() {
    return this->StopName;
}

// direction
string BusStop::getDirection() {
    return this->Direction;
}

// location
string BusStop::getLocationDesc() {
    return this->LocationDesc;
}

// position
pair<double,double> BusStop::getPosition() {
    return this->Position;
}