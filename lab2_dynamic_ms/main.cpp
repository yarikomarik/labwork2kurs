#include "dynMs.h"
#include <iostream>

int main() {
    DynMs a;

    std::cin >> a;
    std::cout << "\nms: " << a << "\n";
    std::cout << "size = " << a.size() << "\n\n";

    a.insert(0, 5);
    a.insert(1, 3);
    a.insert(2, 8);
    a.insert(1, 1);
    std::cout << "ms: " << a << "\n";
    std::cout << "size = " << a.size() << "\n";

    std::cout << "find(8) = " << a.find(8) << "\n";
    std::cout << "find(100) = " << a.find(100) << "\n";

    a.sort();
    std::cout << "after sort: " << a << "\n";

    a.removeAt(0);
    std::cout << "after removeAt(0): " << a << "\n";

    a.removeByValue(8);
    std::cout << "after removeByValue(8): " << a << "\n";

    std::cout << "insert(6, 8888) = " << a.insert(6, 8888) << "\n";
    std::cout << "removeAt(-1) = " << a.removeAt(-1) << "\n";

    std::cout << "iterator test: ";
    for (DynMs::iterator it = a.begin(); it != a.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";

    return 0;
}