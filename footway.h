/*footway.h*/

//
// A footway in the openstreet map.
//

#pragma once

#include <string>
#include <vector>
#include <set>

#include "node.h"
#include "nodes.h"

using namespace std;

//
// Footway
//
// Defines a campus footway in the openstreet map
// with an ID and a vector of NodeIDs.
//

class Footway
{
public:
    long long ID;
    vector<long long> NodeIDs;

    //
    // Constructor
    //
    Footway(long long id);

    //
    // Adds the nodeid to the end of the vector.
    //
    void add(long long nodeid);

    //
    // Sorts the nodeids and removes duplicates
    //
    void sortNodeids();

    //
    // Binary search for a matching nodeid.
    //
    void searchFootway(long long nodeid, set<long long>& foundids);
};