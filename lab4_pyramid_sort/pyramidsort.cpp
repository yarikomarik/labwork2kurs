#include "pyramidsort.h"
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <sstream>

int myrand(int lo, int hi) {
    return lo + rand() % (hi - lo + 1);
}

std::string makeFileName(int n, int lo, int hi) {
    std::ostringstream os;
    os << "array_n" << n << "_lo" << lo << "_hi" << hi << ".bin";
    return os.str();
}

bool saveArray(const std::vector<int>& a, const std::string& filename) {
    std::ofstream out(filename, std::ios::binary);
    if (!out) {
        return false;
    }

    int sz = static_cast<int>(a.size());
    out.write(reinterpret_cast<const char*>(&sz), sizeof(sz));

    if (sz > 0) {
        out.write(reinterpret_cast<const char*>(a.data()),
                  static_cast<std::streamsize>(sz * sizeof(int)));
    }

    return static_cast<bool>(out);
}

bool loadArray(std::vector<int>& a, const std::string& filename) {
    std::ifstream in(filename, std::ios::binary);
    if (!in) {
        return false;
    }

    int sz = 0;
    in.read(reinterpret_cast<char*>(&sz), sizeof(sz));
    if (!in || sz < 0) {
        return false;
    }

    a.resize(sz);

    if (sz > 0) {
        in.read(reinterpret_cast<char*>(a.data()),
                static_cast<std::streamsize>(sz * sizeof(int)));
    }

    return static_cast<bool>(in);
}

void Sift2(int* a, int n, int i) {
    int j = 2 * i + 1;
    int x = a[i];
    int f = 1;

    while (j < n && f) {
        if (j + 1 < n) {
            if (a[j + 1] > a[j]) {
                j = j + 1;
            }
        }

        if (a[j] > x) {
            a[i] = a[j];
            i = j;
            j = 2 * i + 1;
        } else {
            f = 0;
        }
    }

    a[i] = x;
}

void heapSort(int* a, int n) {
    // 1. Построение пирамиды
    for (int i = n / 2 - 1; i >= 0; --i) {
        Sift2(a, n, i);
    }

    // 2. Сортировка
    for (int i = n - 1; i >= 1; --i) {
        std::swap(a[0], a[i]);
        Sift2(a, i, 0);
    }
}

bool isSorted(const std::vector<int>& a) {
    for (int i = 0; i + 1 < static_cast<int>(a.size()); ++i) {
        if (a[i] > a[i + 1]) {
            return false;
        }
    }
    return true;
}