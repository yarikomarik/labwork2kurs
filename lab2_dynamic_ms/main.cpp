#include "dynMs.h"
#include "dynMsT.h"
#include <iostream>

int main() {
    std::cout << "enter test mode(1-2):";
    int mode; std::cin >> mode;
    if (mode==1){
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

        std::cout << "insert(6, 88) = " << a.insert(6, 8888) << "\n";
        std::cout << "removeAt(-1) = " << a.removeAt(-1) << "\n";

        std::cout << "iterator test: ";
        for (DynMs::iterator it = a.begin(); it != a.end(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << "\n";

        a += 3;               
        a += 999;

        std::cout << "a = " << a << "\n";

        std::cout << "min = " << a.min() << ", max = " << a.max() << "\n";

        DynMs::iterator it = a.begin() + 1;
        a.insert(it, 99);
        std::cout << "after insert: " << a << "\n";
        a.removeByIterator(a.begin());
        std::cout << "after removeByIterator(begin()): " << a << "\n";

        a.removeRange(a.begin() + 1, a.begin() + 3);
        std::cout << "after removeRange(1, 3): " << a << "\n";

        int n = a.removeAllByValue(1);
        std::cout << "how many 1 deleted: " << n << ", a = " << a << "\n";

        DynMs b = a + 100;
        std::cout << "b = a + 100: " << b << "\n";

        DynMs c = a + b;
        std::cout << "c = a + b: " << c << "\n";

        DynMs d = std::move(c);
        std::cout << "d: " << d << "\n";

        std::cout << "(a == b)? " << (a == b) << "\n";
        std::cout << "(a != b)? " << (a != b) << "\n";

    }
    if (mode==2){
        DynMsT<std::string> arr;
        arr += "banana";
        arr += "apple";
        arr += "cherry";
        std::cout << "array: " << arr << "\n";
        std::cout << "size: " << arr.size() << ", cap: " << arr.capacity() << "\n\n";

        arr.insert(1, "apricot");
        std::cout << "after insert 'apricot' on pos 1: " << arr << "\n\n";

        int idx = arr.find("cherry");
        std::cout << "index 'cherry': " << idx << "\n";
        std::cout << "index 'grape': " << arr.find("grape") << "\n\n";

        std::cout << "first element: " << arr[0] << "\n";
        arr.sort();
        std::cout << "after sort: " << arr << "\n\n";

        std::cout << "min:" << arr.min() << "\n";
        std::cout << "max: " << arr.max() << "\n\n";

        DynMsT<std::string>::iterator it = arr.begin();
        ++it; 
        arr.insert(it, "avocado");
        std::cout << "after insert 'avocado' before 2nd element: " << arr << "\n\n";

        arr += "apple"; 
        std::cout << "ms before deleting: " << arr << "\n";
        int removed = arr.removeAllByValue("apple");
        std::cout << "deleted 'apple': " << removed << "\n";
        std::cout << "after delete: " << arr << "\n\n";

        it = arr.begin();
        arr.removeByIterator(it);
        std::cout << "after delete by operator: " << arr << "\n\n";

        if (arr.size() >= 2) {
            arr.removeRange(arr.begin() + 1, arr.begin() + 3);
            std::cout << "after delete diaposone [1, 3): " << arr << "\n\n";
        }

        DynMsT<std::string> arr2 = arr; 
        arr2 += "date";
        std::cout << "arr2 (copy arr + 'date'): " << arr2 << "\n";
        
        DynMsT<std::string> arr3 = arr + arr2; 
        std::cout << "arr3 (arr + arr2): " << arr3 << "\n\n";

        std::cout << "arr == arr2: " << (arr == arr2 ? "yes" : "no") << "\n";
        std::cout << "arr != arr2: " << (arr != arr2 ? "yes" : "no") << "\n\n";

        DynMsT<std::string> arr4 = std::move(arr2);
        std::cout << "arr4 (moved arr2): " << arr4 << "\n";
        std::cout << "arr2 after move (cap): " << arr2.size() << "\n\n";
    }
    return 0;
}