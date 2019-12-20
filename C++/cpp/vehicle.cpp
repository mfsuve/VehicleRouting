#include <iostream>
#include "../hpp/vehicle.hpp"
#include "../hpp/customer.hpp"

using namespace std;

Vehicle::Vehicle(int capacity) : load(0), capacity(capacity) {}

bool Vehicle::fits(int demand) const {
    return capacity >= load + demand;
}

bool Vehicle::fits(Customer& c) const {
    return fits(c.demand);
}

bool Vehicle::fits(list<Customer>::iterator i) const {
    return fits(*i);
}

list<Customer>::iterator Vehicle::begin() {
    return route.begin();
}

list<Customer>::iterator Vehicle::end() {
    return route.end();
}

bool Vehicle::empty() {
    return route.empty();
}

Customer& Vehicle::remove(list<Customer>::iterator i) {
   Customer& node = *i;
   route.erase(i);
   load -= node.demand;
   return node; 
}

void Vehicle::add(Customer& node, list<Customer>::iterator i) {
    route.insert(i, node);
    load += node.demand;
}

void Vehicle::add(Customer& node) {
    add(node, end());
}

void Vehicle::add(list<Customer>::iterator node, list<Customer>::iterator i) {
    add(*node, i);
}

void Vehicle::add(list<Customer>::iterator node) {
    add(*node);
}

int Vehicle::getLoad() {
    return load;
}