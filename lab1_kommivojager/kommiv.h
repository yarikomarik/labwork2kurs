#pragma once

struct TSP {
    int n;              
    int** distance;            
    bool* location;         
    int* way;           
    int* bestWay;       
    int bestLen;        
    int worstLen;
};

bool nextPermutation(int* P, int m);
void pereborIterative(TSP& t);
void perebor(TSP& t, int city, int len, int cnt);
void maswap(int *a, int *b);
void scanMatrD(int** matr, int m, int n);
void printMatrD(TSP& t);
void randMatrD(int** matr, int m, int n, int lf, int rt);
void greedyAlg(TSP& t, int startCity);
void fillRandomMatrix(TSP& t, int minCost, int maxCost);
double quality(int minC, int maxC, int greedy) ;