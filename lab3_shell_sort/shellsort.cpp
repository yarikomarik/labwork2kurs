#include "shell_sort.h"

bool isSorted(vector<int>& a) {
    for (int i = 0; i < a.size() - 1; i++) {
        if (a[i] > a[i + 1]) {
            return false;
        }
    }
    return true;
}

void shellSort(vector<int>& a, vector<int> gaps) {
    int n = (int)a.size();

    // идём по шагам от самого большого к 1
    for (int k = (int)gaps.size() - 1; k >= 0; k--) {
        int h = gaps[k];

        // обычная сортировка вставками, но с шагом h
        for (int i = h; i < n; i++) {
            int x = a[i];
            int j = i;

            while (j >= h && a[j - h] > x) {
                a[j] = a[j - h];
                j = j - h;
            }
            a[j] = x;
        }
    }
}

// 1) последовательность Шелла: n/2, n/4, n/8, ..., 1
vector<int> gapsShell(int n) {
    vector<int> gaps;
    int h = n / 2;

    while (h > 0) {
        gaps.push_back(h);
        h = h / 2;
    }

    return gaps;
}

// 2) последовательность Кнута: 1, 4, 13, 40, 121, ...
// каждое следующее = 3 * предыдущее + 1
vector<int> gapsKnuth(int n) {
    vector<int> gaps;
    int h = 1;

    while (h <= n) {
        gaps.push_back(h);
        h = 3 * h + 1;
    }

    return gaps;
}

// 3) последовательность Сэджвика: 1, 5, 19, 41, 109, ...
vector<int> gapsSedgewick(int n) {
    vector<int> gaps;
    int k = 0;

    while (true) {
        long long h;

        if (k % 2 == 0) {
            // h = 9 * (2^k - 2^(k/2)) + 1
            long long p2 = 1LL << k;
            long long p2half = 1LL << (k / 2);
            h = 9 * (p2 - p2half) + 1;
        } else {
            // h = 8 * 2^k - 6 * 2^((k+1)/2) + 1
            long long p2 = 1LL << k;
            long long p2half = 1LL << ((k + 1) / 2);
            h = 8 * p2 - 6 * p2half + 1;
        }

        if (h > n) break;

        gaps.push_back((int)h);
        k++;

        if (k > 60) break; // чтобы не было переполнения
    }

    return gaps;
}