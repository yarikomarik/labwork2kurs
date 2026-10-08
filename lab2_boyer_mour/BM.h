#pragma once

#include <string>
#include <vector>

// Поиск первого вхождения подстроки
int findFirst(const std::string& text, const std::string& pattern);

// Поиск всех вхождений подстроки
std::vector<int> findAll(const std::string& text, const std::string& pattern);

// Поиск вхождений в диапазоне [startPos, endPos]
std::vector<int> findAllInRange(const std::string& text, const std::string& pattern, int startPos, int endPos);