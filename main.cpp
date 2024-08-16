/*main.cpp*/

//
// Program to input Nodes (positions) and Buildings from
// an Open Street Map file.
// 

#include <iostream>
#include <string>
#include <curl/curl.h>

#include "curl_util.h"
#include "footway.h"
#include "footways.h"
#include "building.h"
#include "buildings.h"
#include "busstop.h"
#include "busstops.h"
#include "footway.h"
#include "footways.h"
#include "node.h"
#include "nodes.h"
#include "osm.h"
#include "tinyxml2.h"

using namespace std;
using namespace tinyxml2;


//
// main
//
int main()
{
  tinyxml2::XMLDocument xmldoc;
  Nodes nodes;
  Buildings buildings;
  Footways footways;
  BusStops busstops;
  //
  // initialize CURl library
  //

  CURL *curl = curl_easy_init();
  
  if (curl == nullptr) {
    cout << "**ERROR:" << endl;
    cout << "**ERROR: unable to initialize curl library" << endl;
    cout << "**ERROR:" << endl;
    return 0;
  }

  cout << "** NU open street map **" << endl;

  string filename;

  cout << endl;
  cout << "Enter map filename> " << endl;
  getline(cin, filename);

  //
  // load XML-based map file 
  //
  if (!osmLoadMapFile(filename, xmldoc))
  {
    // failed, error message already output
    return 0;
  }
  
  //
  // read the nodes, which are the various known positions on the map:
  //
  nodes.readMapNodes(xmldoc);

  //
  // read the university buildings:
  //
  buildings.readMapBuildings(xmldoc);

  //
  // read the footways on campus:
  //
  footways.readMapFootways(xmldoc);

  //
  // sort the map footways and remove duplicates:
  //
  footways.sortEach();

  //
  // now read the csv file with bus stops
  //
  string busfilename = "bus-stops.txt";
  busstops.readMapBusStops(busfilename);

  //
  // stats
  //
  cout << "# of nodes: " << nodes.getNumMapNodes() << endl;
  cout << "# of buildings: " << buildings.getNumMapBuildings() << endl;
  cout << "# of bus stops: " << busstops.getNumBusStops() << endl;


  //
  // now let the user for search for 1 or more buildings:
  //
  while (true)
  {
    string name;

    cout << endl;
    cout << "Enter building name (partial or complete), or * to list, or @ for bus stops, or $ to end> " << endl;

    getline(cin, name);

    if (name == "$")
      break;
    else if (name == "*")
      buildings.print();
    else if (name == "@")
      busstops.printAll();
    else
      buildings.findAndPrint(name,nodes,footways,busstops, curl);

  }//while

  //
  // done:
  //
  curl_easy_cleanup(curl);

  cout << endl;
  cout << "** Done **" << endl;

  return 0;
}
