#include <iostream>
#include <iterator>
#include "vehicle.hpp"
#include "tabusearch.hpp"

using namespace std;

Vehicle::Vehicle() : load(0) {}

bool Vehicle::fits(int demand) {
    return capacity >= load + demand;
}

list<int>::iterator Vehicle::begin() {
    return route.begin();
}

list<int>::iterator Vehicle::end() {
    return route.end();
}

int Vehicle::remove(list<int>::iterator i) {
   int node = *i;
   route.erase(i);
   load -= TabuSearch::demands[node];
   return node; 
}

void Vehicle::add(int node, list<int>::iterator i) {
    load += TabuSearch::demands[node];
    route.insert(next(i), node);
}
