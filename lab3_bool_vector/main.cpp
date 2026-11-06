#include "boolvector.h"
#include <iostream>

int main()
{
    BitVector a("11110010");
    BitVector b(8, false);
    BitVector c; 

    
    std::cout << "a         = " << a << "\n";
    std::cout << "b         = " << b << "\nenter c:";
    std::cin>>c;
    std::cout << "c         = " << c << "\n";
    std::cout << "~a        = " << ~a << "\n";
    std::cout << "a & b     = " << (a & b) << "\n";
    std::cout << "a | b     = " << (a | b) << "\n";
    std::cout << "a ^ b     = " << (a ^ b) << "\n";
    std::cout << "a << 3    = " << (a << 3) << "\n";
    std::cout << "a >> 2    = " << (a >> 2) << "\n";
    std::cout << "weight(a) = " << a.weight() << "\n";

    // Работа через BitReference
    a[0] = true;
    a[1] = ~a[2];
    a[3] |= a[4];
    std::cout << "a after   = " << a << "\n";

    return 0;
}