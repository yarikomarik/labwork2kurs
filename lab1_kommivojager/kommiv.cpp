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
#include <climits>
#include <algorithm>
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



//
bool nextPermutation(int* P, int m) {
    int i = m - 2;
    // 1. Находим максимальное i, такое что P[i] < P[i+1]
    while (i >= 0 && P[i] >= P[i+1]) {
        i--;
    }
    if (i < 0) return false; // следующей перестановки нет

    // 2. Находим максимальное j > i, такое что P[i] < P[j]
    int j = m - 1;
    while (P[j] <= P[i]) {
        j--;
    }

    // 3. Меняем P[i] и P[j]
    swap(P[i], P[j]);

    // 4. Инвертируем хвост от i+1 до конца (упорядочиваем по возрастанию)
    reverse(P + i + 1, P + m);
    return true;
}

// Итеративный перебор всех гамильтоновых циклов, начинающихся в городе 0
void pereborIterative(TSP& t) {
    int n = t.n;
    if (n <= 1) {
        t.bestLen = 0;
        t.worstLen = 0;
        if (n == 1) {
            t.bestWay[0] = 0;
            t.bestWay[1] = 0;
        }
        return;
    }

    int m = n - 1; // количество городов, которые нужно переставлять (1..n-1)
    int* P = new int[m];
    for (int i = 0; i < m; ++i) {
        P[i] = i + 1; // начальная перестановка: 1, 2, ..., n-1
    }

    t.bestLen = INT_MAX;
    t.worstLen = -1; // или 0, если все длины положительны

    do {
        // Вычисляем длину маршрута: 0 -> P[0] -> P[1] -> ... -> P[m-1] -> 0
        int total = t.distance[0][P[0]];
        for (int i = 0; i < m - 1; ++i) {
            total += t.distance[P[i]][P[i+1]];
        }
        total += t.distance[P[m-1]][0];

        // Обновляем лучший маршрут
        if (total < t.bestLen) {
            t.bestLen = total;
            t.bestWay[0] = 0;
            for (int i = 0; i < m; ++i) {
                t.bestWay[i + 1] = P[i];
            }
            t.bestWay[n] = 0;
        }

        // Обновляем худший маршрут
        if (total > t.worstLen) {
            t.worstLen = total;
        }

    } while (nextPermutation(P, m));

    delete[] P;
}
//
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