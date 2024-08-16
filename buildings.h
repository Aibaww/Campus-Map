/*buildings.h*/

//
// A collection of buildings in the Open Street Map.
//

#pragma once

#include <vector>

#include "footways.h"
#include "building.h"
#include "busstops.h"
#include "tinyxml2.h"

using namespace std;
using namespace tinyxml2;


//
// Keeps track of all the buildings in the map.
//
class Buildings
{
public:
  vector<Building> MapBuildings;

  //
  // readMapBuildings
  //
  // Given an XML document, reads through the document and 
  // stores all the buildings into the given vector.
  //
  void readMapBuildings(XMLDocument &xmldoc);

  //
  // Prints all the buildings in the map.
  //
  void print();

  //
  // finds a building in the map with the given name and prints some info.
  // can find intersecting footways or closest busstops
  //
  void findAndPrint(string& name, Nodes& nodes, Footways& footways, BusStops& busstops, CURL* curl);

  //
  // accessors / getters
  //
  int getNumMapBuildings();

};


