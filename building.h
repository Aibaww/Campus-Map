/*building.h*/

//
// A building in the Open Street Map.
//

#pragma once

#include <string>
#include <vector>
#include <curl/curl.h>

#include "curl_util.h"
#include "footways.h"
#include "busstops.h"
#include "node.h"
#include "nodes.h"

using namespace std;

//
// Building
//
// Defines a campus building with a name (e.g. "Mudd"), a street
// address (e.g. "2233 Tech Dr"), and the IDs of the nodes that
// define the position / outline of the building.
//
// NOTE: the Name could be empty "", the HouseNumber could be
// empty, and the Street could be empty. Imperfect data.
//
class Building
{
public:
  long long ID;
  string Name;
  string StreetAddress;
  vector<long long> NodeIDs;

  //
  // constructor
  //
  Building(long long id, string name, string streetAddr);

  //
  // adds the given nodeid to the end of the vector.
  //
  void add(long long nodeid);

  //
  // prints information about the building.
  //
  void print(Nodes &nodes, BusStops& busstops, CURL* curl);

  //
  // searches for a footway that intersects with this building.
  //
  void findIntersectingFootway(Footways &footways);

  //
  // gets the center (lat, lon) of the building based
  // on the nodes that form the perimeter
  //
  pair<double, double> getLocation(const Nodes &nodes);
};
