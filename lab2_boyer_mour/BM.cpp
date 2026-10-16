#include "BM.h"
#include <algorithm>

#include <vector>
#include <string>

std::vector<int> makeTable(const std::string& pattern) {
    int m = pattern.size();
    std::vector<int> table(256, m); 
    for (int i = 0; i < m - 1; i++) {
        table[(unsigned char)pattern[i]] = m - 1 - i;
    }
    return table;
}

int boyerMourBased(int n, int m, char* s, char* p) {
    std::vector<int> table = makeTable(std::string(p, m)); 

    int i = m - 1; // i — индекс конца текущего окна в тексте
    while (i < n) {
        int k = i;       // k — текщий индекс в тексте
        int j = m - 1;   // j — текущий индекс в шаблоне
        int tmp = 0;     // tmp — количество совпавших символов

        while (j >= 0) {
            if (s[k] == p[j]) {
                --k; --j; ++tmp;
            } else {
                break;
            }
        }

        if (j < 0) {
            return k + 1;
        } else {
            i += (table[(unsigned char)s[k]] - tmp);
        }
    }
    return -1;
}
int findFirst(const std::string& text, const std::string& pattern) {
    int n = text.size();
    int m = pattern.size();
    if (m == 0 || m > n) return -1;
    
    return boyerMourBased(n, m, const_cast<char*>(text.c_str()), const_cast<char*>(pattern.c_str()));
}

std::vector<int> findAll(const std::string& text, const std::string& pattern) {
    std::vector<int> res;
    int n = text.size();
    int m = pattern.size();
    if (m == 0 || m > n) return res;

    int pos = 0;
    while (pos <= n - m) {
        int found = boyerMourBased(n - pos, m, const_cast<char*>(text.c_str() + pos), const_cast<char*>(pattern.c_str()));
        if (found == -1) break;

        int absolutePos = pos + found;
        res.push_back(absolutePos);

        pos = absolutePos + 1;
    }
    return res;
}

std::vector<int> findAllInRange(const std::string& text, const std::string& pattern, 
                                int startPos, int endPos) {
    std::vector<int> res;
    int n = text.size();
    int m = pattern.size();

    if (m == 0 || startPos < 0 || endPos >= n || startPos > endPos) return res;
    if (m > (endPos - startPos + 1)) return res;

    int pos = startPos;
    while (pos <= endPos - m + 1) {
        int remainingLen = endPos - pos + 1;

        int found = boyerMourBased(remainingLen, m, 
                                   const_cast<char*>(text.c_str() + pos), 
                                   const_cast<char*>(pattern.c_str()));
        if (found == -1) break;

        int absolutePos = pos + found;
        res.push_back(absolutePos);

        pos = absolutePos + 1;
    }
    return res;
}
