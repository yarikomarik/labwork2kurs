#include "BM.h"
#include <algorithm>

std::vector<int> makeTable(const std::string& pattern) {
    std::vector<int> table(256, -1);
    for (int i = 0; i < (int)pattern.size(); i++) {
        table[(unsigned char)pattern[i]] = i;
    }
    return table;
}

std::vector<int> search(const std::string& text, const std::string& pattern) {
    std::vector<int> res;
    int n = text.size();
    int m = pattern.size();

    if (m == 0 || m > n) return res;

    std::vector<int> table = makeTable(pattern);

    int shift = 0;
    while (shift <= n - m) {
        int j = m - 1;

        while (j >= 0 && pattern[j] == text[shift + j]) {
            j--;
        }

        if (j < 0) {
            res.push_back(shift);
            if (shift + m < n)
                shift += m - table[(unsigned char)text[shift + m]];
            else
                shift += 1;
        } else {
            int badShift = j - table[(unsigned char)text[shift + j]];
            if (badShift < 1) badShift = 1;
            shift += badShift;
        }
    }
    return res;
}

int findFirst(const std::string& text, const std::string& pattern) {
    std::vector<int> v = search(text, pattern);
    if (v.size() == 0) return -1;
    return v[0];
}

std::vector<int> findAll(const std::string& text, const std::string& pattern) {
    return search(text, pattern);
}

std::vector<int> findAllInRange(const std::string& text, const std::string& pattern, int startPos, int endPos) {
    std::vector<int> res;
    int n = text.size();

    if (startPos < 0 || endPos >= n || startPos > endPos) return res;

    std::string part = text.substr(startPos, endPos - startPos + 1);
    std::vector<int> found = search(part, pattern);

    for (int i = 0; i < (int)found.size(); i++) {
        res.push_back(found[i] + startPos);
    }
    return res;
}