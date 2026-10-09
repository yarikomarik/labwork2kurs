#include "kommiv.h"
#include <iomanip>
#include <ios>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <iterator>
#include <chrono>
#include <random>

using namespace std;

int main() {
    int sizes[]    = { 4, 6, 8, 10 };
    int maxCosts[] = { 10, 100 };

    for (int maxC : maxCosts) {
        for (int n : sizes) {
            cout << "\n=== n = " << n << ", stoimosti 1.." << maxC << " ===\n";

            for (int trial = 1; trial <= 3; trial++) {
                TSP t;
                t.n = n;

                // выделяем память
                t.distance = new int*[n];
                for (int i = 0; i < n; i++) t.distance[i] = new int[n];
                t.location    = new bool[n];
                t.way     = new int[n + 1];
                t.bestWay = new int[n + 1];
                t.bestLen = 1000000000;
                t.worstLen = 0;

                fillRandomMatrix(t, 1, maxC);

                cout << "\nMatrica:\n";
                printMatrD(t);

                // полный перебор
                auto t0 = chrono::high_resolution_clock::now();
                pereborIterative(t);
                auto t1 = chrono::high_resolution_clock::now();
                double tb = chrono::duration<double>(t1 - t0).count();

                cout << "perebor:  cost = " << t.bestLen << ", time = " << fixed << setprecision(9) << tb << " s , worst = " << t.worstLen << "\n";

                // запоминаем оптимальны, чтобы не перезаписать жадным
                int optMin = t.bestLen;
                int optMax = t.worstLen;

                // жадный алгоритм
                t.bestLen = 1000000000;
                auto t2 = chrono::high_resolution_clock::now();
                greedyAlg(t, 0);
                auto t3 = chrono::high_resolution_clock::now();
                double tg = chrono::duration<double>(t3 - t2).count();

                cout << "greedy:   cost = " << t.bestLen << ", time = " << fixed << setprecision(9) << tg << " s\n";

                cout << "Kachestvo: " << quality(optMin, optMax, t.bestLen) << " %\n";

                // освобождаем память
                for (int i = 0; i < n; i++) 
                    delete[] t.distance[i];
                delete[] t.distance;
                delete[] t.location;
                delete[] t.way;
                delete[] t.bestWay;
            }
        }
    }
    return 0;
}