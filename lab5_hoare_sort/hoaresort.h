#pragma once

#include <vector>
#include <string>

void quickSortHoare(int arr[], int l, int r);
int myrand(int lo, int hi);

std::string makeFileName(int n, int lo, int hi);

bool saveArray(std::vector<int>& a, std::string filename);

bool loadArray(std::vector<int>& a, std::string filename);

bool isSorted(std::vector<int>& a);
