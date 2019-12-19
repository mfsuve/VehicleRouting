#ifndef VEHICLE_HPP
#define VEHICLE_HPP
#include <iostream>
#include <list>
#include "../hpp/customer.hpp"

using namespace std;

class Vehicle {
public:
    list<Customer> route;
    Vehicle(int capacity);
    bool fits(int demand) const;
    bool fits(Customer& c) const;
    bool fits(list<Customer>::iterator i) const;
    list<Customer>::iterator begin();
    list<Customer>::iterator end();
    Customer remove(list<Customer>::iterator i);
    void add(Customer& node, list<Customer>::iterator i);
    void add(Customer& node);
    bool empty();
private:
    int capacity;
    int load;
};
#endif