#include <iostream>
#include "../hpp/vehicle.hpp"
#include "../hpp/customer.hpp"

using namespace std;

Vehicle::Vehicle(int capacity) : load(0), capacity(capacity) {}

bool Vehicle::fits(int demand) const {
    return capacity >= load + demand;
}

bool Vehicle::fits(const Customer* c) const {
    return fits(c->demand);
}

bool Vehicle::fits(list<Customer*>::const_iterator i) const {
    return fits(*i);
}

list<Customer*>::const_iterator Vehicle::begin() {
    return route.cbegin();
}

list<Customer*>::const_iterator Vehicle::end() {
    return route.cend();
}

bool Vehicle::empty() const {
    return route.empty();
}

void Vehicle::removeLast() {
    auto removeIterator = prev(end());
    load -= (*removeIterator)->demand;
    route.erase(removeIterator);
}

Customer* Vehicle::remove(list<Customer*>::const_iterator i) {
   Customer* node = *i;
   route.erase(i);
   load -= node->demand;
   return node;
}

void Vehicle::add(Customer* node, list<Customer*>::const_iterator i) {
    route.insert(i, node);
    load += node->demand;
}

void Vehicle::add(Customer* node) {
    add(node, end());
}

void Vehicle::add(list<Customer*>::const_iterator node, list<Customer*>::const_iterator i) {
    add(*node, i);
}

void Vehicle::add(list<Customer*>::const_iterator node) {
    add(*node);
}

void Vehicle::clear() {
    route.clear();
    load = 0;
}

int Vehicle::getLoad() const {
    return load;
}
