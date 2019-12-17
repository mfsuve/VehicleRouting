#include <iostream>
#include <vector>
#include "../hpp/tabulist.hpp"
#include "../hpp/vehicle.hpp"
#include "../hpp/customer.hpp"

using namespace std;

class TabuSearch {
public:
    int N, V, c;
    static vector<int> demands;
    TabuSearch(const char* filename);
    void solve(int iterations, int tenure);
private:
    int cost;
    double distance(const int& i, const int& j);
    int updateToBestNeighbor(Vehicle vehicles[], TabuList& tabulist);
    vector<double> distances;
};
