#include <iostream>
#include <cstdlib>
#include "../hpp/tabusearch.hpp"

using namespace std;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " filename";
        return 0;
    }
    srand(0);
    TabuSearch solver(argv[1], false);
}
