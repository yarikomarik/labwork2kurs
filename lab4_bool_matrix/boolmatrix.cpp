#include "boolmatrix.h"

//Конструкторы / деструктор

BoolMatrix::BoolMatrix() {
    cols = 0;
}

BoolMatrix::BoolMatrix(int r, int c, bool value) {
    cols = (c > 0) ? c : 0;
    if (r > 0 && cols > 0) {
        BitVector row(cols, value);
        for (int i = 0; i < r; i++) {
            rows.insert(rows.size(), row);
        }
    }
}

BoolMatrix::BoolMatrix(const char** mat, int r) {
    cols = 0;
    if (mat == nullptr || r <= 0) return;

    // определяем количество столбцов по первой строке
    int c = 0;
    while (mat[0][c] == '0' || mat[0][c] == '1') c++;
    cols = c;
    if (cols == 0) return;

    for (int i = 0; i < r; i++) {
        BitVector row(cols, false);
        for (int j = 0; j < cols; j++) {
            if (mat[i][j] == '1') row.set(j, true);
        }
        rows.insert(rows.size(), row);
    }
}

BoolMatrix::BoolMatrix(const BoolMatrix& other) {
    rows = other.rows;
    cols = other.cols;
}

BoolMatrix::~BoolMatrix() { }

//Размеры и обмен

int BoolMatrix::rowCount() const { return rows.size(); }
int BoolMatrix::colCount() const { return cols; }

void BoolMatrix::swap(BoolMatrix& other) {
    rows.swap(other.rows);
    int t = cols; cols = other.cols; other.cols = t;
}

//Характеристики

int BoolMatrix::weight() const {
    int w = 0;
    for (int i = 0; i < rows.size(); i++) {
        w += rows[i].weight();
    }
    return w;
}

int BoolMatrix::rowWeight(int j) const {
    return rows[j].weight();
}

//Конъюнкция / дизъюнкция всех строк

BitVector BoolMatrix::conjunctRows() const {
    // пустая конъюнкция — все единицы
    BitVector res(cols, true);
    for (int i = 0; i < rows.size(); i++) {
        res &= rows[i];
    }
    return res;
}

BitVector BoolMatrix::disjunctRows() const {
    // пустая дизъюнкция — все нули
    BitVector res(cols, false);
    for (int i = 0; i < rows.size(); i++) {
        res |= rows[i];
    }
    return res;
}

//Изменение битов

void BoolMatrix::invertBit(int i, int j) {
    rows[j].invert(i);
}

void BoolMatrix::invertBits(int i, int k, int j) {
    for (int t = 0; t < k && (i + t) < cols; t++) {
        rows[j].invert(i + t);
    }
}

void BoolMatrix::setBit(int i, int j, bool value) {
    rows[j].set(i, value);
}

void BoolMatrix::setBits(int i, int k, int j, bool value) {
    rows[j].set(i, k, value);
}

//Доступ по индексу 

BitVector& BoolMatrix::operator[](int i) {
    return rows[i];
}

const BitVector& BoolMatrix::operator[](int i) const {
    return rows[i];
}

//Присваивание

BoolMatrix& BoolMatrix::operator=(const BoolMatrix& other) {
    if (this == &other) return *this;
    BoolMatrix tmp(other);
    swap(tmp);
    return *this;
}

//Построчные compound-операции  

BoolMatrix& BoolMatrix::operator&=(const BoolMatrix& other) {
    for (int i = 0; i < rowCount(); i++) {
        if (i < other.rowCount()) {
            rows[i] &= other[i];   // BitVector::&= сам обнулит "лишние" биты
        } else {
            rows[i].setAll(false);
        }
    }
    return *this;
}

BoolMatrix& BoolMatrix::operator|=(const BoolMatrix& other) {
    int r = (rowCount() < other.rowCount()) ? rowCount() : other.rowCount();
    for (int i = 0; i < r; i++) {
        rows[i] |= other[i];
    }
    return *this;
}

BoolMatrix& BoolMatrix::operator^=(const BoolMatrix& other) {
    int r = (rowCount() < other.rowCount()) ? rowCount() : other.rowCount();
    for (int i = 0; i < r; i++) {
        rows[i] ^= other[i];
    }
    return *this;
}

//   Построчные бинарные операции  

BoolMatrix operator&(const BoolMatrix& a, const BoolMatrix& b) {
    int r = (a.rowCount() < b.rowCount()) ? a.rowCount() : b.rowCount();
    int c = (a.colCount() < b.colCount()) ? a.colCount() : b.colCount();
    BoolMatrix res(r, c, false);
    for (int i = 0; i < r; i++) {
        res[i] = a[i] & b[i];   // BitVector::& возвращает вектор минимальной длины
    }
    return res;
}

BoolMatrix operator|(const BoolMatrix& a, const BoolMatrix& b) {
    int r = (a.rowCount() < b.rowCount()) ? a.rowCount() : b.rowCount();
    int c = (a.colCount() < b.colCount()) ? a.colCount() : b.colCount();
    BoolMatrix res(r, c, false);
    for (int i = 0; i < r; i++) {
        res[i] = a[i] | b[i];
    }
    return res;
}

BoolMatrix operator^(const BoolMatrix& a, const BoolMatrix& b) {
    int r = (a.rowCount() < b.rowCount()) ? a.rowCount() : b.rowCount();
    int c = (a.colCount() < b.colCount()) ? a.colCount() : b.colCount();
    BoolMatrix res(r, c, false);
    for (int i = 0; i < r; i++) {
        res[i] = a[i] ^ b[i];
    }
    return res;
}

BoolMatrix operator~(const BoolMatrix& a) {
    BoolMatrix res(a);
    for (int i = 0; i < res.rowCount(); i++) {
        res[i].invert();
    }
    return res;
}

//   Ввод / вывод  

std::ostream& operator<<(std::ostream& os, const BoolMatrix& m) {
    for (int i = 0; i < m.rowCount(); i++) {
        os << m[i];
        if (i != m.rowCount() - 1) os << '\n';
    }
    return os;
}

std::istream& operator>>(std::istream& is, BoolMatrix& m) {
    int r, c;
    std::cout << "Количество строк: ";
    is >> r;
    std::cout << "Количество столбцов: ";
    is >> c;

    BoolMatrix tmp(r, c, false);
    for (int i = 0; i < r; i++) {
        std::string s;
        std::cout << "Строка " << (i + 1) << ": ";
        is >> s;
        int len = (int)s.length();
        if (len > c) len = c;
        for (int j = 0; j < len; j++) {
            tmp[i][j] = (s[j] == '1');   // BitReference::operator=(bool)
        }
    }
    m = tmp;
    return is;
}