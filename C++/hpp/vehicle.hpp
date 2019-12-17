#ifndef VEHICLE_HPP
#define VEHICLE_HPP
#include <iostream>
#include <list>

using namespace std;

class Vehicle {
public:
    list<Customer> route;
    Vehicle();
    bool fits(int demand);
    bool Vehicle::fits(Customer& c);
    bool Vehicle::fits(list<Customer>::iterator i);
    list<Customer>::iterator begin();
    list<Customer>::iterator end();
    Customer remove(list<Customer>::iterator i);
    void add(Customer node, list<Customer>::iterator i);
private:
    int capacity;
    int load;
};
#endif