#include "boolmatrix.h"
#include <iostream>

int main()
{
    BoolMatrix a(3, 4, false);
    a.setBit(0, 0, true);
    a.setBit(1, 1, true);
    a.setBit(3, 2, true);

    BoolMatrix b(3, 4, true);

    const char* raw[] = { "1010", "0101", "1100" };
    BoolMatrix c(raw, 3);

    BoolMatrix d;   // пустая

    std::cout << "a (bit):\n" << a << "\n\n";
    std::cout << "b (all 1):\n" << b << "\n\n";
    std::cout << "c (char**):\n" << c << "\n\n";
    std::cout << "d (empty): rows=" << d.rowCount() << " cols=" << d.colCount() << "\n\n";

    std::cout << "a.weight():     " << a.weight() << "\n";
    std::cout << "b.weight():     " << b.weight() << "\n";
    std::cout << "c.weight():     " << c.weight() << "\n";
    std::cout << "c.rowWeight(0): " << c.rowWeight(0) << "\n";
    std::cout << "c.rowWeight(2): " << c.rowWeight(2) << "\n\n";

    std::cout << "c.conjunctRows(): " << c.conjunctRows() << "\n";
    std::cout << "c.disjunctRows(): " << c.disjunctRows() << "\n\n";

    std::cout << "a & b:\n" << (a & b) << "\n\n";
    std::cout << "a | b:\n" << (a | b) << "\n\n";
    std::cout << "a ^ b:\n" << (a ^ b) << "\n\n";
    std::cout << "~c :\n" << (~c) << "\n\n";

    // составные операции
    BoolMatrix t = c;
    t &= b;
    std::cout << "c &= b:\n" << t << "\n\n";

    t = c;
    t |= a;
    std::cout << "c |= a:\n" << t << "\n\n";

    t = c;
    t ^= a;
    std::cout << "c ^= a:\n" << t << "\n\n";

    // копирование и присваивание
    BoolMatrix copy(c);
    copy.setBit(0, 0, false);
    std::cout << "copy(c), but copy[0][0]=0:\n" << copy << "\n";
    std::cout << "c[0][0] = " << (c[0][0] ? 1 : 0) << "\n\n";

    BoolMatrix assigned;
    assigned = c;
    std::cout << "assigned = c:\n" << assigned << "\n\n";

    // swap
    BoolMatrix m1(2, 3, true);
    BoolMatrix m2(4, 5, false);
    m1.swap(m2);
    std::cout << "after swap: m1 rows=" << m1.rowCount() << " cols=" << m1.colCount() << " weight=" << m1.weight() << "\n";
    std::cout << "after swap: m2 rows=" << m2.rowCount() << " cols=" << m2.colCount() << " weight=" << m2.weight() << "\n\n";

    // инверсия битов и диапазона
    BoolMatrix e(1, 6, false);
    e.setBit(0, 0, true);
    e.setBits(1, 3, 0, true);           // 1111 00 -> 111100
    std::cout << "e after setBits   = " << e[0] << "\n";
    e.invertBit(5, 0);                  // инвертируем последний
    std::cout << "e after invertBit = " << e[0] << "\n";
    e.invertBits(0, 4, 0);              // инвертим первые 4
    std::cout << "e after invertBits= " << e[0] << "\n\n";

    // запись через operator[] (BitReference внутри BitVector)
    std::cout << "c[0] = " << c[0] << "\n";
    c[0][2] = true;
    c[0][3] = ~c[0][0];
    std::cout << "c[0] after correct:" << c[0] << "\n";

    return 0;
}