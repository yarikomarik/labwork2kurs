#include <cstddef>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "kommiv.h"
#include <climits>
#include <ctime>
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
void randMatrD(int** matr, int m, int n, int lf, int rt) {
    srand(time(0));
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            matr[i][j] = rand() % (rt - lf + 1) + lf;
}

void go(TSP& t, int city, int len, int cnt) {
    t.way[cnt] = city;

    // прошли все города — возвращаемся в стартовый (0)
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