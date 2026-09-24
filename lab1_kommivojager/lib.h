#pragma once

void randMs(int* ms, int n, int lf, int rt);
void printMs(int* ms, int n);
int max(int a, int b);
int min(int a, int b);
void gnomeSort(int* ms, int n);
void gnomeSortRev(int* ms, int n);
int prost(int n);
void maswap(int* a, int* b);
void scanMs(int* ms, int n);
void ShiftLeft(int* a, int n, int pos);
void ShiftLeft_k(int* a, int n, int p, int k);
int maxMs(int* ms, int n);
int minMs(int* ms, int n);
void Vstavka(int* a, int n, int k);
int mafind(int* a, int n, int k);

void scanMatr(int matr[][100], int m, int n);
void printMatr(int matr[][100], int m, int n);
void randMatr(int matr[][100], int m, int n, int lf, int rt);
void minMatr(int matr[][100], int m, int n, int* i_min, int* j_min);
void maxMatr(int matr[][100], int m, int n, int* i_max, int* j_max);
void scanMatrD(int** matr, int m, int n);
void printMatrD(int** matr, int m, int n);
int DelCol(int** matr, int m, int n, int k);
int DelStrS(int** matr, int m, int n, int k);
int DelStrD(int** matr, int m, int n, int k);
void randMatrD(int** matr, int m, int n, int lf, int rt);

bool number(char ch);
bool Letter(char ch);
bool letter(char ch);
int findSpace(char s[], int i);
int space(char s[], int i);
int comma(char s[], int i);

int Definebit(unsigned int value, int k);
void outputBV(unsigned int x, int n);
unsigned int setUp1(unsigned int x, int k);
unsigned int input1BV(char s[], int n);
unsigned int input2BV (char s[], int n);
void inputBM (unsigned int *bm, int m, int n);
void outputBM (unsigned int *bm, int m, int n);
int weightСolumn(unsigned int *bm, int m, int k);

void createRandFile(const char *name, int n, int lf, int rt);
void printFile(const char *name);
int fibonacci(int n);
int Ifibonacci(int n);
void sliyanie(const char *name, const char *name1, const char *name2);
int linSearch(int* a, int n, int k);
int linSearchBarier(int* a, int n, int k);
int binSearch(int  a[], int n, int k);
void randMsVosrast(int* ms, int n, int mn, int mx);
int boyerMour(int n, int m, char* s, char* p);
int boyerMourBased(int n, int m, char* s, char* p);
void sliyanieFeof(const char *name, const char *name1, const char *name2);
void BubbleSort(int *a, int n);
void updBubbleSort(int *a, int n);
void shakerSortUpd(int *a, int n);
void shakerSort(int *a, int n);
void vstavkaBinSearchSort(int * a, int n);

int sum(int a, int b, int c);