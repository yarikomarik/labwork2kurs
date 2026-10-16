#include "BM.h"
#include <iostream>
#include <string>
#include <vector>

int main() {
    std::string text = "obama_chmobam";
    std::string pattern = "bam";
    int left = 3, right = 6;

    std::cout << "text:    " << text << "\n";
    std::cout << "pattern: " << pattern << "\n\n";

    std::cout << "findFirst: " << findFirst(text, pattern) << "\n";

    std::vector<int> all = findAll(text, pattern);
    std::cout << "findAll: ";
    for (int i = 0; i < (int)all.size(); i++)
        std::cout << all[i] << " ";
    std::cout << "\n";

    std::vector<int> r1 = findAllInRange(text, pattern, left, right);
    std::cout << "findAllInRange(" << left << ", " << right << "): ";
    for (int i = 0; i < (int)r1.size(); i++)
        std::cout << r1[i] << " ";
    std::cout << "\n";

    return 0;
}