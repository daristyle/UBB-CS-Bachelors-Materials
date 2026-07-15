#pragma once

#include "../Repository/Repository.h"

using std::pair;

class Service {
private:
    Repository& repo;

public:
    Service(Repository& repo);

    vector<Flight> getFlights();
    vector<Flight> getFlightsSorted();
    vector<Flight> getDelayedFlights(int delay);
    pair<vector<Flight>, int> getFlightsAndTotalDelay(string destination, int hour, int minute);
};