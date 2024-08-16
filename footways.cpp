/*footways.cpp*/

//
// A collection of footways.
//

#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <bits/stdc++.h> 

#include "footways.h"
#include "osm.h"
#include "tinyxml2.h"

using namespace std;
using namespace tinyxml2;

//
// readMapFootways
//
// Given an XML document, reads through the document and
// stores all the footways in MapFootways.
//
void Footways::readMapFootways(XMLDocument& xmldoc)
{
  XMLElement* osm = xmldoc.FirstChildElement("osm");
  assert(osm != nullptr);

  //
  // Parse the XML document way by way, looking for university buildings:
  //
  XMLElement* way = osm->FirstChildElement("way");

  while (way != nullptr)
  {
    const XMLAttribute* attr = way->FindAttribute("id");
    assert(attr != nullptr);

    //
    // if this is a footway, store info into vector:
    //
    if (osmContainsKeyValue(way, "highway", "footway") || osmContainsKeyValue(way, "area:highway", "footway"))
    {

      //
      // create footway object, then add the associated
      // node ids to the object:
      //
      long long id = attr->Int64Value();
      Footway footway(id);

      XMLElement* nd = way->FirstChildElement("nd");

      while (nd != nullptr)
      {
        const XMLAttribute* ndref = nd->FindAttribute("ref");
        assert(ndref != nullptr);

        long long nodeid = ndref->Int64Value();

        footway.add(nodeid);

        // advance to next node ref:
        nd = nd->NextSiblingElement("nd");
      }

      //
      // add the footway to the vector:
      //
      
      this->MapFootways.push_back(footway);
    }//if

    way = way->NextSiblingElement("way");
  }//while

  //
  // done:
  //
}

//
// getters:
//
int Footways::getNumMapFootways() {
  return (int) this->MapFootways.size();
}

//bool compareID(Footway i, Footway j)
//{
//  return (i.ID < j.ID);
//}

//
// sortEach:
//
// sorts the nodeids of each footway in MapFootways
//
void Footways::sortEach()
{
  //sort(this->MapFootways.begin(), this->MapFootways.end(), compareID);
  // this->MapFootways.erase(unique(this->MapFootways.begin(), this->MapFootways.end()), this->MapFootways.end());
  for (int i = 0; i < (int) this->MapFootways.size(); i++)
  {
    this->MapFootways[i].sortNodeids();
  }
}

//
// find given nodeid in a vector of footways
//
void Footways::searchFootways(long long nodeid, set<long long>& foundids)
{
  for (int i = 0; i < (int) this->MapFootways.size(); i++) {
    this->MapFootways[i].searchFootway(nodeid, foundids);
  }
}