#include <iostream>
#include <vector>
#include <list>
#include "../hpp/customer.hpp"
#include "../hpp/vehicle.hpp"

using namespace std;

class Greedy {
public:
    double cost;
    Greedy(int N, int V, bool verbose=false);
private:
    bool verbose;
    int numUnvisited, N, V;
};
