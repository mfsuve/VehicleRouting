#include <iostream>
#include <list>

using namespace std;

int main() {
    list<int> ints;
    for (int i = 0; i < 5; ++i)
        ints.push_back(i);
    
    list<int>::iterator it = ints.begin();

    list<int>::iterator it2 = it;

}
