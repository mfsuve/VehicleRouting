#ifndef VEHICLE_HPP
#define VEHICLE_HPP
#include <iostream>
#include <list>

using namespace std;

class Vehicle {
public:
    list<int> route;
    Vehicle();
    bool fits(int demand);
    list<int>::iterator begin();
    list<int>::iterator end();
    int remove(list<int>::iterator i);
    void add(int node, list<int>::iterator i);
private:
    int capacity;
    int load;
};
#endif