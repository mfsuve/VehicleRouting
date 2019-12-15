#include <iostream>
#include <vector>

using namespace std;

class TabuList {
public:
    int N, tenure;
    vector<int> tabulist;
    TabuList(int N, int tenure);
    void makeTabu(int i, int j, int maxDelay=5);
    bool isTabu(int i, int j);
    void step();
    int index(int i, int j);
};