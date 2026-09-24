#include <cstddef>
#include <cstdlib>
#include <stdio.h>
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
//вывод динамической матрицы
void printMatrD(int** matr, int m, int n){
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++)
            printf("%d ", matr[i][j]);
        printf("\n");
    }
} 
//создает случайну динамическую матрицу m n с диапозоном случайных числел от lf до rt
void fillRandomMatrix(int** matrix, int nCities, int minCost, int maxCost) {
    std::random_device randomDevice;
    std::mt19937 generator(randomDevice());
    std::uniform_int_distribution<int> distribution(minCost, maxCost);

    for (int i = 0; i < nCities; i++) {
        matrix[i][i] = 0;   // из города в себя — 0
        for (int j = i + 1; j < nCities; j++) {
            int value = distribution(generator);
            matrix[i][j] = value;
            matrix[j][i] = value;   // зеркально — та же дорога
        }
    }
}
void go(TSP& t, int city, int len, int cnt) {
    t.way[cnt] = city;

    if (cnt == t.n - 1) {
        int total = len + t.distance[city][0];
        if (total < t.bestLen) {
            t.bestLen = total;
            for (int i = 0; i < t.n; i++) t.bestWay[i] = t.way[i];
            t.bestWay[t.n] = 0;
        }
        return;
    }

    t.location[city] = true;

    for (int next = 0; next < t.n; next++) {
        if (!t.location[next]) {
            go(t, next, len + t.distance[city][next], cnt + 1);
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