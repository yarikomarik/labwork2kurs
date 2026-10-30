#pragma once
#include <vector>
#include <string>
using namespace std;

int myrand(int lo, int hi);

std::string makeFileName(int n, int lo, int hi);
bool saveArray(vector<int>& a, string filename);
bool loadArray(vector<int>& a, string filename);

bool isSorted(vector<int>& a);

void shellSort(vector<int>& a, vector<int> gaps);

vector<int> gapsShell(int n);
vector<int> gapsKnuth(int n);
vector<int> gapsSedgewick(int n);