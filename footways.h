/*footways.h*/

//
// A collection of footways in the Open Street Map.
//

#pragma once

#include <vector>

#include "footway.h"
#include "tinyxml2.h"

using namespace std;
using namespace tinyxml2;

//
// Keeps track of all the footways in the Open Street Map.
//
class Footways
{
    public:
        vector<Footway> MapFootways;

    //
    // Given an XML document, reads through the document and
    // stores all the footways in MapFootways.
    //
    void readMapFootways(XMLDocument& doc);

    //
    // getters
    //
    int getNumMapFootways();

    //
    // find given nodeid in a vector of footways
    //
    void searchFootways(long long nodeid, set<long long>& foundids);

    //
    // Sorts the nodeids of each footway.
    //
    void sortEach();
};