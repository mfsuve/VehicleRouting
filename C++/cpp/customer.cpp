#include <iostream>
#include <list>
#include <cmath>
#include "../hpp/customer.hpp"

using namespace std;

Customer::Customer(int id, int demand, double x, double y) : id(id), demand(demand), x(x), y(y), visited(false) {}

Customer::Customer(const Customer& other) : id(other.id), demand(other.demand), x(other.x), y(other.y), visited(other.visited) {
    for (double d : other.distances)
        distances.push_back(d);
}

bool Customer::operator==(const Customer& customer) {
    return id == customer.id;
}

bool Customer::isWarehouse() const {
    return id == 0;
}

double Customer::distance(list<Customer*>::const_iterator i) const {
    return distance(*i);
}

double Customer::distance(const Customer* to) const {
    return distances[to->id];
}

double Customer::distance(int i) const {
    return distances[i];
}

void Customer::addNeighbor(Customer* neighbor) {
    if (neighbor == this)
        distances.push_back(0);
    else {
        double distance = hypot(x - neighbor->getX(), y - neighbor->getY());
        distances.push_back(distance);
        neighbor->distances.push_back(distance);
    }
}

int Customer::getX() const {
    return x;
}

int Customer::getY() const {
    return y;
}
