#pragma once
#include <vector>
using namespace std;

int myrand(int lo, int hi);

bool isSorted(vector<int>& a);

void shellSort(vector<int>& a, vector<int> gaps);

vector<int> gapsShell(int n);
vector<int> gapsKnuth(int n);
vector<int> gapsSedgewick(int n);