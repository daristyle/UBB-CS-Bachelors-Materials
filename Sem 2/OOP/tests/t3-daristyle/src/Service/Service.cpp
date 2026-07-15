#include "Service.h"

#include <algorithm>

Service::Service(Repository& _repo): repo(_repo){
}

vector<Flight> Service::getFlights(){
    return repo.getFlights();
}

vector<Flight> Service::getFlightsSorted(){
    auto flights = getFlights();
    sort(flights.begin(), flights.end(), [](Flight& a, Flight& b){
        if(a.getHour() != b.getHour()){
            return a.getHour() > b.getHour();
        }
        return a.getMinute() > b.getMinute();
    });

    return flights;
}

vector<Flight> Service::getDelayedFlights(int delay){
    auto flights = getFlightsSorted();
    vector<Flight> delayed;
    for(const auto& flight: flights){
        if(flight.getDelay() > delay) delayed.push_back(flight);
    }
    return delayed;
}

pair<vector<Flight>, int> Service::getFlightsAndTotalDelay(string destination, int hour, int minute){
    auto flights = getFlightsSorted();
    vector<Flight> filtered;
    int totalDelay = 0;
    for(const auto& flight: flights){
        if(flight.getDestination() == destination && (flight.getHour() > hour ||
            (flight.getHour() == hour && flight.getMinute() >= minute))){
            filtered.push_back(flight);
            totalDelay += flight.getDelay();
        }
    }
    return {filtered, totalDelay};
}
