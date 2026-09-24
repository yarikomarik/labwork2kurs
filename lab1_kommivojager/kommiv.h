#pragma once

struct TSP {
    int n;              
    int** distance;            
    bool* location;         
    int* way;           
    int* bestWay;       
    int bestLen;        
};

void go(TSP& t, int city, int len, int cnt);
void maswap(int *a, int *b);
void scanMatrD(int** matr, int m, int n);
void printMatrD(int** matr, int m, int n);
void randMatrD(int** matr, int m, int n, int lf, int rt);
void greedyAlg(TSP& t, int startCity);
void fillRandomMatrix(int** matrix, int nCities, int minCost, int maxCost);