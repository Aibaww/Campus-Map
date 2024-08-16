/*footway.cpp*/

//
// A footway in the Open Street Map.
//

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <bits/stdc++.h> 

#include "footway.h"
#include "nodes.h"

using namespace std;

//
// constructor
//
Footway::Footway(long long id)
    : ID(id)
{
}

//
// add
//
void Footway::add(long long nodeid)
{
  this->NodeIDs.push_back(nodeid);
}

//
// sort the nodeIDs with the vector method
//
void Footway::sortNodeids()
{
  sort(this->NodeIDs.begin(), this->NodeIDs.end());
  //this->NodeIDs.erase(unique (this->NodeIDs.begin(), this->NodeIDs.end()), this->NodeIDs.end());

  // set<long long> s(this->NodeIDs.begin(), this->NodeIDs.end());
  // this->NodeIDs.assign(s.begin(), s.end());
}

//
// binary search for a matching nodeID
//
void Footway::searchFootway(long long nodeid, set<long long>& foundids)
{

  int low = 0;
  int high = this->NodeIDs.size() - 1;

  while (low <= high) {
    int mid = low + (high - low) / 2;

    if (this->NodeIDs[mid] == nodeid) { // found it
      foundids.insert(this->ID);
      return;
    }
    else if (this->NodeIDs[mid] < nodeid) { // search right
      low = mid + 1;
    }
    else { // search left
      high = mid - 1;
    }
  }

  // // not found
}