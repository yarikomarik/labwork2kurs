#include "shellsort.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

//новый ранд для больших чисел
int myrand(int lo, int hi) {
    int r = (rand() << 15) | rand();
    int range = hi - lo + 1;
    return lo + r % range;
}

//проверка сортировки
bool isSorted(vector<int>& a) {
    for (int i = 0; i < a.size() - 1; i++) {
        if (a[i] > a[i + 1]) {
            return false;
        }
    }
    return true;
}

//сортировка Шелла
void shellSort(vector<int>& a, vector<int> gaps) {
    int n = (int)a.size();
    int t = (int)gaps.size() - 1;

    for (int i = 0; i <= t; i++) {
        int s = gaps[i];
        int b = 0;

        while (b < s) {
            int j = b + s;
            while (j < n) {
                int x = a[j];
                int k = j - s;
                while (k >= 0 && a[k] > x) {
                    a[k + s] = a[k];
                    k = k - s;
                }
                a[k + s] = x;
                j = j + s;
            }
            b++;
        }
    }
}
//последовательность Шелла: n/2, n/4, n/8
vector<int> gapsShell(int n) {
    vector<int> gaps;
    int h = n / 2;
    while (h > 0) {
        gaps.push_back(h);
        h = h / 2;
    }
    return gaps;
}

//последовательность Кнута: 1, 4, 13, 40, 121
vector<int> gapsKnuth(int n) {
    vector<int> tmp;
    int h = 1;
    while (h <= n) {
        tmp.push_back(h);
        h = 3 * h + 1;
    }
    vector<int> gaps;
    for (int i = (int)tmp.size() - 1; i >= 0; i--) {
        gaps.push_back(tmp[i]);
    }
    return gaps;
}

//последовательность Сэджвика: 1, 5, 19, 41, 109
vector<int> gapsSedgewick(int n) {
    vector<int> tmp;
    int k = 0;

    while (true) {
        long long h;
        if (k % 2 == 0) {
            long long p2 = 1LL << k;
            long long p2half = 1LL << (k / 2);
            h = 9 * (p2 - p2half) + 1;
        } else {
            long long p2 = 1LL << k;
            long long p2half = 1LL << ((k + 1) / 2);
            h = 8 * p2 - 6 * p2half + 1;
        }
        if (h > n) break;
        tmp.push_back((int)h);
        k++;
        if (k > 60) break;
    }

    vector<int> gaps;
    for (int i = (int)tmp.size() - 1; i >= 0; i--) {
        gaps.push_back(tmp[i]);
    }
    return gaps;
}
