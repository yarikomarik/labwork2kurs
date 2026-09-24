#include "kommiv.h"
#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

int main()
{
    TSP t;
    t.bestLen=10000000;
    int** distance = new int *[t.n];
    t.location=new bool[t.n];
    t.way = new int[t.n + 1];
    t.bestWay = new int[t.n + 1];

    for (int i = 0; i < t.n; i++) 
        t.distance[i] = new int[t.n];

    cout<<"enter n:";
    cin>>t.n;

    
    randMatrD(distance, t.n, t.n, 1, 10);
    printMatrD(distance, t.n, t.n);
    
    cout << "Minimalnaya dlina: " << t.bestLen << endl;
    cout << "Put: ";
    for (int i = 0; i <= t.n; i++) {
        cout << t.bestWay[i];
        if (i != t.n) cout << " -> ";
    }
    cout << endl;

    // освобождаем память
    for (int i = 0; i < t.n; i++) delete[] t.distance[i];
    delete[] t.distance;
    delete[] t.location;
    delete[] t.way;
    delete[] t.bestWay;

}
