#include "kommiv.h"
#include <iostream>
#include <cmath>
#include <algorithm>
#include <random>

using namespace std;

int main()
{
    TSP t;
    t.bestLen=10000000;
    t.distance = new int*[t.n];
    t.location=new bool[t.n];
    t.way = new int[t.n + 1];
    t.bestWay = new int[t.n + 1];

    for (int i = 0; i < t.n; i++) 
        t.distance[i] = new int[t.n];

    cout<<"enter n:";
    cin>>t.n;

    
    fillRandomMatrix(t.distance, t.n, 1, 9);
    printMatrD(t.distance, t.n, t.n);

    //go(t, 0, 0, 0);
    greedyAlg(t, 0);

    cout << "min len:" << t.bestLen << endl;
    cout << "way: ";
    for (int i = 0; i <= t.n; i++) {
        cout << t.bestWay[i];
    }
    cout << endl;

    for (int i = 0; i < t.n; i++) delete[] t.distance[i];
    delete[] t.distance;
    delete[] t.location;
    delete[] t.way;
    delete[] t.bestWay;

}
