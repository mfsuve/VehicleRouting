#ifndef VEHICLE_HPP
#define VEHICLE_HPP
#include <iostream>
#include <list>

using namespace std;

class Vehicle {
public:
    list<Customer> route;
    Vehicle();
    bool fits(int demand) const;
    bool fits(Customer& c) const;
    bool fits(list<Customer>::iterator i) const;
    list<Customer>::iterator begin();
    list<Customer>::iterator end();
    Customer remove(list<Customer>::iterator i);
    void add(Customer node, list<Customer>::iterator i);
    bool empty();
    static int capacity;
private:
    int load;
};
#endif