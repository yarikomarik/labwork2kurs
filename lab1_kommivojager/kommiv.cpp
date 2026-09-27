#include <cstddef>
#include <cstdlib>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "kommiv.h"
#include <climits>
#include <ctime>
#include <random>
#define UI unsigned int
using namespace std;

void maswap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
//ввод динамической матрицы
void scanMatrD(int** matr, int m, int n){
    for (int i = 0; i < m; i++) 
        for (int j = 0; j < n; j++) 
            scanf("%d", &matr[i][j]);
}
void fillRandomMatrix(TSP& t, int minC, int maxC) {
    static bool seeded = false;
    if (!seeded) { srand(time(0)); seeded = true; }

    int range = maxC - minC + 1;
    for (int i = 0; i < t.n; i++) {
        t.distance[i][i] = 0;
        for (int j = i + 1; j < t.n; j++) {
            int v = minC + rand() % range;
            t.distance[i][j] = v;
            t.distance[j][i] = v;
        }
    }
}

// ---------- печать матрицы ----------
void printMatrD(TSP& t) {
    for (int i = 0; i < t.n; i++) {
        for (int j = 0; j < t.n; j++) {
            cout << t.distance[i][j] << "\t";
        }
        cout << "\n";
    }
}
void perebor(TSP& t, int city, int len, int cnt) {
    t.way[cnt] = city;

    if (cnt == t.n - 1) {
        int total = len + t.distance[city][0];
        if (total < t.bestLen) {
            t.bestLen = total;
            for (int i = 0; i < t.n; i++) 
                t.bestWay[i] = t.way[i];
            t.bestWay[t.n] = 0;
        }
        if (total > t.worstLen) {
            t.worstLen = total;
        }
        return;
    }

    t.location[city] = true;

    for (int next = 0; next < t.n; next++) {
        if (!t.location[next]) {
            perebor(t, next, len + t.distance[city][next], cnt + 1);
        }
    }

    t.location[city] = false;
}

void greedyAlg(TSP& t, int startCity) {
    for (int i = 0; i < t.n; i++) {
        t.location[i] = false;
    }

    int current = startCity;
    t.location[current] = true;

    t.way[0] = startCity;
    t.bestWay[0] = startCity;

    int len = 0; 
    int cnt = 1; 

    for (int step = 0; step < t.n - 1; step++) {
        int bestCity = -1;
        int bestDist = 1000000000;

        for (int next = 0; next < t.n; next++) {
            if (!t.location[next] && t.distance[current][next] < bestDist) {
                bestDist = t.distance[current][next];
                bestCity = next;
            }
        }

        t.location[bestCity] = true;
        len += bestDist;
        current = bestCity;

        t.way[cnt] = current;
        t.bestWay[cnt] = current;
        cnt++;
    }

    len += t.distance[current][startCity];
    t.way[cnt] = startCity;
    t.bestWay[cnt] = startCity;
    cnt++;

    t.bestLen = len;
}
double quality(int minC, int maxC, int greedy) {
    if (maxC == minC) 
        return 100.0;
    return (double)(maxC - greedy) / (maxC - minC) * 100.0;
}