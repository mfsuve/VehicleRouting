#include <iostream>
#include "../hpp/vehicle.hpp"
#include "../hpp/customer.hpp"

using namespace std;

Vehicle::Vehicle() : load(0) {}

bool Vehicle::fits(int demand) const {
    cout << "Vehicle capacity is " << capacity << endl;
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

Customer Vehicle::remove(list<Customer>::iterator i) {
   Customer node = *i;
   route.erase(i);
   load -= node.demand;
   return node; 
}

void Vehicle::add(Customer node, list<Customer>::iterator i) {
    route.insert(i, node);
    load += node.demand;
}
