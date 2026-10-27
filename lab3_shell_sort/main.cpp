#include "shellsort.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

int main() {
    srand(time(0));

    int sizes[3] = {10000, 100000, 1000000};
    int lows[3] = {-10, -1000, -100000};
    int highs[3] = {10, 1000, 100000};

    for (int s = 0; s < 3; s++) {
        int n = sizes[s];

        for (int r = 0; r < 3; r++) {
            int lo = lows[r];
            int hi = highs[r];

            //заполняем массив
            vector<int> base(n);
            for (int i = 0; i < n; i++) {
                base[i] = myrand(lo, hi);
            }

            cout << "n = " << n << ", range = [" << lo << "; " << hi << "]" << endl;

            //сортировка Шелла
            vector<int> a1 = base;
            vector<int> g1 = gapsShell(n);
            clock_t t1 = clock();
            shellSort(a1, g1);
            clock_t t2 = clock();
            double time1 = (double)(t2 - t1) / CLOCKS_PER_SEC;

            if (isSorted(a1)) {
                cout << "  Shell:     yes, time = " << time1 << " s" << endl;
            } else {
                cout << "  Shell:     no" << endl;
            }

            //сортировка Кнута
            vector<int> a2 = base;
            vector<int> g2 = gapsKnuth(n);
            clock_t t3 = clock();
            shellSort(a2, g2);
            clock_t t4 = clock();
            double time2 = (double)(t4 - t3) / CLOCKS_PER_SEC;

            if (isSorted(a2)) {
                cout << "  Knuth:     yes, time = " << time2 << " s" << endl;
            } else {
                cout << "  Knuth:     no" << endl;
            }

            //сортировка Сэджвика
            vector<int> a3 = base;
            vector<int> g3 = gapsSedgewick(n);
            clock_t t5 = clock();
            shellSort(a3, g3);
            clock_t t6 = clock();
            double time3 = (double)(t6 - t5) / CLOCKS_PER_SEC;

            if (isSorted(a3)) {
                cout << "  Sedgewick: yes, time = " << time3 << " s" << endl;
            } else {
                cout << "  Sedgewick: no" << endl;
            }

            cout << endl;
        }
    }
    return 0;
}