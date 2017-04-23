#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <fstream>
#include <vector>

using namespace std;
//
// Created by lirfu on 05.04.17..
//

int main() {
    int MAXPRO = 100, ITEMNUM = 100, SIZE;
    int i, wght, pro;
    // Statictics
    int min, max;
    double avg;
    srand(time(NULL));

    cout << "Please enter the knapsack size: ";
    cin >> SIZE;
    cout << "Please enter the items number: ";
    cin >> ITEMNUM;
    cout << "Please enter the maximum profit: ";
    cin >> MAXPRO;

    ofstream file("KnapsackTest");
    if (file.is_open()) {

        vector<int> weights;
        vector<int> profits;

        // First.
        wght = rand() % SIZE + 1;
        pro = rand() % MAXPRO + 1;
        weights.push_back(wght);
        profits.push_back(pro);

        // Init stat.
        avg = wght;
        min = max = wght;

        for (i = 1; i < ITEMNUM; i++) {
            wght = rand() % SIZE + 1;
            pro = rand() % MAXPRO + 1;
            weights.push_back(wght);
            profits.push_back(pro);
            avg += wght;

            if (wght < min) min = wght;
            if (wght > max) max = wght;
        }

        avg /= ITEMNUM;

        file << "# Built for knapsack of size: " << SIZE << endl;
        file << "# Number of items: " << ITEMNUM << endl;
        file << "# Maximum profit: " << MAXPRO << endl;
        file << "# Weight statistics:" << endl;
        file << "# \tmin: " << min << endl;
        file << "# \tmax: " << max << endl;
        file << "# \tavg: " << avg << endl;

        for (i = 0; i < weights.size(); i++) {
            file << weights[i] << " " << profits[i] << endl;
        }

    } else {
        cout << "Unable to open file" << endl;
        file.close();
    }

    return 0;
}

