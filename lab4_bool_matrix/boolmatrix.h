#pragma once
#include <iostream>
#include "boolvector.h"
#include "dynMsT.h"

class BoolMatrix {
private:
    DynMsT<BitVector> rows;// массив строк-векторов
    int cols;// количество столбцов

public:
    // Конструкторы / деструктор
    BoolMatrix();
    BoolMatrix(int r, int c, bool value = false);
    BoolMatrix(const char** mat, int r);
    BoolMatrix(const BoolMatrix& other);
    ~BoolMatrix();

    // Размеры
    int rowCount() const;
    int colCount() const;

    // Обмен
    void swap(BoolMatrix& other);

    // Характеристики
    int weight() const;// общий вес матрицы
    int rowWeight(int j) const;// вес j-й строки

    // Конъюнкция / дизъюнкция всех строк
    BitVector conjunctRows() const;
    BitVector disjunctRows() const;

    // Изменение битов
    void invertBit(int i, int j); // инверсия i-й компоненты j-й строки
    void invertBits(int i, int k, int j); // инверсия k компонент начиная с i-й
    void setBit(int i, int j, bool value); // установка i-й компоненты j-й строки
    void setBits(int i, int k, int j, bool value); // установка k компонент

    // Доступ к строкам
    BitVector&       operator[](int i);
    const BitVector& operator[](int i) const;

    // Присваивание
    BoolMatrix& operator=(const BoolMatrix& other);

    // Построчные побитовые операции
    BoolMatrix& operator&=(const BoolMatrix& other);
    BoolMatrix& operator|=(const BoolMatrix& other);
    BoolMatrix& operator^=(const BoolMatrix& other);

    friend BoolMatrix operator&(const BoolMatrix& a, const BoolMatrix& b);
    friend BoolMatrix operator|(const BoolMatrix& a, const BoolMatrix& b);
    friend BoolMatrix operator^(const BoolMatrix& a, const BoolMatrix& b);
    friend BoolMatrix operator~(const BoolMatrix& a);

    // Ввод / вывод
    friend std::ostream& operator<<(std::ostream& os, const BoolMatrix& m);
    friend std::istream& operator>>(std::istream& is, BoolMatrix& m);
};