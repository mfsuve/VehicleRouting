#ifndef VEHICLE_HPP
#define VEHICLE_HPP
#include <iostream>
#include <list>
#include "../hpp/customer.hpp"

using namespace std;

// TODO put function has any 0 distance customer?

class Vehicle {
public:
    list<Customer*> route;
    Vehicle(int capacity);
    bool fits(int demand) const;
    bool fits(const Customer* c) const;
    bool fits(list<Customer*>::const_iterator i) const;
    list<Customer*>::const_iterator begin();
    list<Customer*>::const_iterator end();
    Customer* remove(list<Customer*>::const_iterator i);
    void add(Customer* node, list<Customer*>::const_iterator i);
    void add(Customer* node);
    void add(list<Customer*>::const_iterator node, list<Customer*>::const_iterator i);
    void add(list<Customer*>::const_iterator node);
    bool empty() const;
    int getLoad() const;
    bool anyZeroCustomer();
private:
    int capacity, load;
};
#endif