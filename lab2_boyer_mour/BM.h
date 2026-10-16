#pragma once

#include <string>
#include <vector>
std::vector<int> makeTable(const std::string& pattern);

int boyerMourBased(int n, int m, const char* s, const char* p);

int findFirst(const std::string& text, const std::string& pattern);
std::vector<int> findAll(const std::string& text, const std::string& pattern);
std::vector<int> findAllInRange(const std::string& text, const std::string& pattern, int startPos, int endPos);