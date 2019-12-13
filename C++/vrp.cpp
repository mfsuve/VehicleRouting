#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>

using namespace std;

vector<float> distances;

int distance(const int& i, const int& j) {
    if (i == j) return 0;
    int idx;
    if (i > j)
        idx = (i * (i - 1)) / 2 + j;
    else
        idx = (j * (j - 1)) / 2 + i;
    return distances[idx];
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " filename";
        return 0;
    }
    
    // Reading
    // * Can put these into TabuSearch class
    int N, V, c;
    vector<int> demands;
    {
        ifstream file(argv[1]);
        file >> N >> V >> c;
        cout << N << " customers, " << V << " vehicles with capacity " << c << endl;
        vector<int> xs, ys;
        int demand, x, y;
        for (int i = 0; i < N; ++i) {
            file >> demand >> x >> y;
            demands.push_back(demand);
            xs.push_back(x);
            ys.push_back(y);
        }
        file.close();
        for (int i = 1; i < N; ++i)
            for (int j = 0; j < i; ++j)
                distances.push_back(hypot(xs[i] - xs[j], ys[i] - ys[j]));
    }


}
