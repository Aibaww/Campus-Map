/*busstops.cpp*/

//
// A collection of bus stops on the NU Campus map
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <utility>
#include <curl/curl.h>
#include <stdexcept>

#include "json.hpp"
#include "curl_util.h"
#include "busstops.h"
#include "busstop.h"
#include "dist.h"

using json = nlohmann::json;

bool compareBusStops(BusStop& busStop1, BusStop& busStop2) {
    int id1;
    int id2;

    id1 = busStop1.getStopID();
    id2 = busStop2.getStopID();

    return (id1 < id2);
}


void BusStops::readMapBusStops(string& filename)
{
    //
    // open the csv file
    //
    ifstream input;
    input.open(filename);

    if (!input.is_open()) {
        cout << "**failed to open file**" << endl;
        return;
    }

    while (!input.eof()) {
        //
        // read one line from input file
        //
        string line;
        getline(input, line);
   
        if (input.fail()) {
            break; // end of file
        }

        stringstream parser(line); // set up to parse the line
        string stopID, busRoute, stopName, direction, locationDesc, lat, lon;

        getline(parser, stopID, ',');
        getline(parser, busRoute, ',');
        getline(parser, stopName, ',');
        getline(parser, direction, ',');
        getline(parser, locationDesc, ',');
        getline(parser, lat, ',');
        getline(parser, lon);

        pair<double,double> position = make_pair(stod(lat), stod(lon));

        //
        // construct current busStop and put in vector
        //
        BusStop curr(stoi(stopID), stoi(busRoute), stopName, direction, locationDesc, position);
        this->mapBusStops.emplace_back(curr);
        
        // go to next line
    }
    //
    // sort the mapBusStops vector by stopID
    //
    sort(this->mapBusStops.begin(), this->mapBusStops.end(), compareBusStops);
};

//
// print all bus stops
//
void BusStops::printAll() {
    for (auto busStop : this->mapBusStops) {
        busStop.print();
    }
};

//
// predictBusArrival
//
void BusStops::predictBusArrival(BusStop& busstop, CURL* curl, string& response) {
    // setup the request URL
    string myAPIKey = "ExCdTPSD6TyijExYYG7aewhKD";
    string URL = "https://ctabustracker.com/bustime/api/v2/getpredictions?key="+ myAPIKey + "&rt=" + 
    to_string(busstop.getBusRoute()) + "&stpid=" + to_string(busstop.getStopID()) + "&format=json";

    bool success = callWebServer(curl, URL, response);

    if (!success) {
        cout << "  <<bus predictions unavailable, call failed>>" << endl;
        return;
    }
    else {
        // use the json library to parse the data
        auto jsondata = json::parse(response);
        auto bus_response = jsondata["bustime-response"];
        auto predictions = bus_response["prd"];

        if (predictions.size() == 0) {
            cout << "  <<no predictions available>>" << endl;
        }

        // for each prediction (a map) in the list:
        for (auto& M : predictions) {
            try{
                std::cout << " vehicle #" << stoi(M["vid"].get_ref<std::string &>())
                     << " on route " << stoi(M["rt"].get_ref<std::string &>())
                     << " travelling " << M["rtdir"].get_ref<std::string &>()
                     << " to arrive in " << stoi(M["prdctdn"].get_ref<std::string &>()) << " mins" << endl;
                // prdctdn more like predict DEEZ NUTS
            }
            catch (exception& e) {
                std::cout << "  error" << endl;
                std::cout << "  malformed CTA response, prediction unavailable"
                << "(error: " << e.what() << ")" << std::endl;
            }
        }
    }
}

//
// getClosestBusStop
//
void BusStops::getClosestBusStop(pair<double, double> location, CURL* curl) {
    //
    // initialize locations to compare to
    //
    double southdist = 10000;
    double northdist = 10000;
    BusStop southBusStop;
    BusStop northBusStop;

    for (auto busStop : this->mapBusStops) {
        pair<double, double> busStopPosition = busStop.getPosition();
        string direction = busStop.getDirection();

        double dist = distBetween2Points(busStopPosition.first, busStopPosition.second, location.first, location.second);

        //
        // if distance is closer, update closest distance and busstop
        // else do nothing
        //
        if (direction == "Southbound" && dist < southdist) {
            southdist = dist;
            southBusStop = busStop;
        }
        else if (direction == "Northbound" && dist < northdist) {
            northdist = dist;
            northBusStop = busStop;
        }
    }

    //
    // print some info
    //

    cout << "Closest southbound bus stop:" << endl;
    cout << "  " << southBusStop.getStopID() << ": " << southBusStop.getStopName()
    << ", bus #" << southBusStop.getBusRoute() << ", " << southBusStop.getLocationDesc()
    << ", " << southdist << " miles" << endl;

    // get predictions for southbound bus stop
    string predictionSouth;
    predictBusArrival(southBusStop, curl, predictionSouth);

    cout << "Closest northbound bus stop:" << endl;
    cout << "  " << northBusStop.getStopID() << ": " << northBusStop.getStopName()
    << ", bus #" << northBusStop.getBusRoute() << ", " << northBusStop.getLocationDesc()
    << ", " << northdist << " miles" << endl;
    
    // get predictions for northbound bus stop
    string predictionNorth;
    predictBusArrival(northBusStop, curl, predictionNorth);
    
    // done!
    return;
}

//
// get the number of bus stops
//
int BusStops::getNumBusStops() {
    return this->mapBusStops.size();
}