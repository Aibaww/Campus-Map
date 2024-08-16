/*building.cpp*/

//
// A building in the Open Street Map.
//
// Aibaww
//

#include <iostream>
#include <string>
#include <utility>
#include <curl/curl.h>

#include "curl_util.h"
#include "busstop.h"
#include "busstops.h"
#include "building.h"
#include "footways.h"
#include "nodes.h"
#include "node.h"

using namespace std;

//
// constructor
//
Building::Building(long long id, string name, string streetAddr)
    : ID(id), Name(name), StreetAddress(streetAddr)
{
  //
  // the proper technique is to use member initialization list above,
  // in the same order as the data members are declared:
  //
  // this->ID = id;
  // this->Name = name;
  // this->StreetAddress = streetAddr;

  // vector is default initialized by its constructor
}

//
// adds the given nodeid to the end of the vector.
//
void Building::add(long long nodeid)
{
  this->NodeIDs.push_back(nodeid);
}

//
// prints information about this building.
//
void Building::print(Nodes& nodes, BusStops& busstops, CURL* curl)
{
  cout << this->Name << endl;
  cout << "Address: " << this->StreetAddress << endl;
  cout << "Building ID: " << this->ID << endl;
  cout << "# perimeter nodes: " << this->NodeIDs.size() << endl;

  pair<double,double> location = this->getLocation(nodes);
  cout << "Location: (" << location.first << ", " << location.second << ")" << endl;

  //
  // find closest busstops
  //
  
  busstops.getClosestBusStop(location, curl);

  return;
  
  //
  // print all nodes of this building:
  //

  // cout << "Nodes: " << this->NodeIDs.size() << endl;
  // for (long long nodeid : this->NodeIDs)
  // {
  //   cout << " " << nodeid << ": ";

  //   double lat = 0.0;
  //   double lon = 0.0;
  //   bool entrance = false;

  //   bool found = nodes.find(nodeid, lat, lon, entrance);

  //   if (found) {
  //     cout << "(" << lat << ", " << lon << ")";

  //     if (entrance)
  //       cout << ", is entrance";

  //     cout << endl;
  //   }
  //   else {
  //     cout << "**NOT FOUND**" << endl;
  //   }
  // }
}

//
// searches for a footway that intersects with this building.
//
void Building::findIntersectingFootway(Footways& footways)
{
  set<long long> foundids;

  for (long long nodeid : this->NodeIDs)
  {
    footways.searchFootways(nodeid, foundids);
  }

  cout << "Footways that intersect: " << foundids.size() << endl;
  if (foundids.size() == 0)
  {
    cout << " None" << endl;
  }
  else
  {
    for (long long id : foundids)
    {
      cout << " Footway " << id << endl;
    }
  }
}

//
// gets the center (lat, lon) of the building based
// on the nodes that form the perimeter
//
pair<double, double> Building::getLocation(const Nodes& nodes)
{
  double avglat = 0.0;
  double avglon = 0.0;

  for (long long nodeid : this->NodeIDs) // for each node of building
  {
    double lat = 0.0;
    double lon = 0.0;
    bool entrance = false;

    bool found = nodes.find(nodeid, lat, lon, entrance); // search for node in all nodes

    if (found) { // if found, add the lat and lon to the total
      avglat += lat;
      avglon += lon;
    }
  }

  avglat /= this->NodeIDs.size();
  avglon /= this->NodeIDs.size();

  return make_pair(avglat, avglon);
}