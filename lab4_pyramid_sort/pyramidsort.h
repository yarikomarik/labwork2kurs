#pragma once

#include <vector>
#include <string>

int myrand(int lo, int hi);

std::string makeFileName(int n, int lo, int hi);
bool saveArray(const std::vector<int>& a, const std::string& filename);
bool loadArray(std::vector<int>& a, const std::string& filename);

// Просеивание i-го элемента через пирамиду 
void Sift2(int* a, int n, int i);
//пирамидальная сортировка
void heapSort(int* a, int n);
//проверка массива
bool isSorted(const std::vector<int>& a);