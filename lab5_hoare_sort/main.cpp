#include "hoaresort.h"
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    cout << "enter mode(1-2)" << endl;
    cout << "  1 - generate ms" << endl;
    cout << "  2 - use old ms" << endl;

    int mode;
    cin >> mode;

    int sizes[3] = {10000, 100000, 1000000};
    int lows[3]  = {-10, -1000, -100000};
    int highs[3] = {10, 1000, 100000};

    for (int s = 0; s < 3; ++s) {
        int n = sizes[s];

        for (int r = 0; r < 3; ++r) {
            int lo = lows[r];
            int hi = highs[r];

            string filename = makeFileName(n, lo, hi);
            vector<int> base;

            if (mode == 1) {
                // генерация
                base.resize(n);
                for (int i = 0; i < n; ++i) {
                    base[i] = myrand(lo, hi);
                }

                if (!saveArray(base, filename)) {
                    cerr << "cannot save: " << filename << endl;
                    continue;
                }
            }
            if (mode == 2){
                // чтение
                if (!loadArray(base, filename)) {
                    cout << "  skip: cannot load " << filename << endl << endl;
                    continue;
                }

                if (static_cast<int>(base.size()) != n) {
                    cout << filename
                         << " expected " << n
                         << " got " << base.size() << endl;
                    continue;
                }
            }

            cout << "n = " << n << ", range = [" << lo << "; " << hi << "]" << endl;

            double totalTime = 0.0;
            bool allSorted = true;

            for (int run = 0; run < 3; ++run) {
                vector<int> a = base;

                clock_t t1 = clock();
                quickSortHoare(a.data(), 0, static_cast<int>(a.size()) - 1);
                clock_t t2 = clock();

                totalTime += static_cast<double>(t2 - t1) / CLOCKS_PER_SEC;

                if (!isSorted(a)) {
                    allSorted = false;
                }
            }

            double avgTime = totalTime / 3;

            cout << "QuickSort: " << (allSorted ? "yes" : "no") 
                 << ", time = " << fixed << setprecision(6) << avgTime << " s" << endl << endl;
        }
    }

    return 0;
}