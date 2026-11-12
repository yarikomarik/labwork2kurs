#include "quicksort.h"
#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

//быстрая сортировка Хоара
void quickSortHoare3(int arr[], int l, int r) {
    //если l >= r, то выход
    if (l >= r) {
        return;
    }

    int i = l;
    int j = r;
    int x = arr[(l + r) / 2]; // Опорный элемент (эталон) берем из середины

    while (i <= j) {
        while (arr[i] < x) {
            i++;
        }
        
        while (arr[j] > x) {
            j--;
        }
        if (i <= j) {
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;

            i++;
            j--;
        }
    }

    //для фрагмента от l до j
    quickSortHoare3(arr, l, j);
    
    //для фрагмента от i до r
    quickSortHoare3(arr, i, r);
}


// новый ранд для больших чисел
int myrand(int lo, int hi) {
    long long range = (long long)hi - lo + 1;
    long long r = ((long long)rand() * 32768LL + rand()) % range;
    return (int)(lo + r);
}

// имя файла по параметрам массива
string makeFileName(int n, int lo, int hi) {
    return "array_n" + to_string(n)
         + "_r" + to_string(lo)
         + "_" + to_string(hi) + ".txt";
}

// сохранить массив в файл (по одному числу на строку)
bool saveArray(vector<int>& a, string filename) {
    ofstream f(filename.c_str());
    if (!f.is_open()) {
        cout << "cant create file " << filename << endl;
        return false;
    }
    for (int i = 0; i < (int)a.size(); i++) {
        f << a[i] << "\n";   // "\n", а не endl — иначе миллион строк пишется медленно
    }
    f.close();
    return true;
}

// прочитать массив из файла
bool loadArray(vector<int>& a, string filename) {
    a.clear();
    ifstream f(filename.c_str());
    if (!f.is_open()) {
        cout << "file not found: " << filename << endl;
        return false;
    }
    int x;
    while (f >> x) {
        a.push_back(x);
    }
    return true;
}

// проверка сортировки
bool isSorted(vector<int>& a) {
    for (int i = 0; i < (int)a.size() - 1; i++) {
        if (a[i] > a[i + 1]) {
            return false;
        }
    }
    return true;
}