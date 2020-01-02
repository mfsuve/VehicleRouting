#include <iostream>
#include <list>
#include <iterator>

using namespace std;

void print(list<int> l) {
    for (auto it = l.begin(); it != l.end(); ++it)
        cout << *it << " ";
    cout << endl;
}

int main() {
    list<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    l.push_back(4);
    l.push_back(5);
    l.push_back(6);
    print(l);

    auto it1 = l.begin();
    advance(it1, 3);
    auto it2 = l.begin();
    advance(it2, 3);

    cout << *it1 << " " << *it2 << endl;

    l.erase(it1);

    cout << *it1 << " " << *it2 << endl;

    print(l);

    cout << (it1 == it2) << endl;

}
