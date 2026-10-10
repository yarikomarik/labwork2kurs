#include "BM.h"
#include <algorithm>

std::vector<int> makeTable(const std::string& pattern) {
    std::vector<int> table(256, -1);
    for (int i = 0; i < (int)pattern.size(); i++) {
        table[(unsigned char)pattern[i]] = i;
    }
    return table;
}

int bmsearch(const std::string& text, const std::string& pattern, int startPos = 0, int endPos = -1) {
    int n = text.size();
    if (endPos == -1 || endPos >= n) {
        endPos = n - 1;
    }
    int m = pattern.size();

    if (m == 0 || startPos < 0 || startPos > endPos || m > (endPos - startPos + 1)) return -1;

    std::vector<int> table = makeTable(pattern);

    int shift = startPos;
    while (shift <= endPos - m + 1) {
        int j = m - 1;

        while (j >= 0 && pattern[j] == text[shift + j]) {
            j--;
        }

        if (j < 0) {
            return shift;
        } else {
            int badShift = j - table[(unsigned char)text[shift + j]];
            if (badShift < 1) badShift = 1;
            shift += badShift;
        }
    }
    return -1;
}

int findFirst(const std::string& text, const std::string& pattern) {
    return bmsearch(text, pattern, 0, text.size() - 1);
}

std::vector<int> findAll(const std::string& text, const std::string& pattern) {
    std::vector<int> res;
    int m = pattern.size();
    if (m == 0) return res;

    int pos = bmsearch(text, pattern, 0, text.size() - 1);
    while (pos != -1) {
        res.push_back(pos);
        pos = bmsearch(text, pattern, pos + 1, text.size() - 1);
    }
    return res;
}

std::vector<int> findAllInRange(const std::string& text, const std::string& pattern, int startPos, int endPos) {
    std::vector<int> res;
    int m = pattern.size();
    if (m == 0 || startPos < 0 || endPos >= (int)text.size() || startPos > endPos) return res;

    int pos = bmsearch(text, pattern, startPos, endPos);
    while (pos != -1) {
        res.push_back(pos);
        pos = bmsearch(text, pattern, pos + 1, endPos);
    }
    return res;
}
