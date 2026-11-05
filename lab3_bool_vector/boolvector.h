#ifndef BITVECTOR_H
#define BITVECTOR_H

#include <iostream>
#include <string>

class BitVector {
public:
    // Класс-обёртка для работы с отдельным битом
    class BitReference {
    public:
        BitReference(unsigned char* p, int pos);
        BitReference(const BitReference& other);

        BitReference& operator=(bool value);
        BitReference& operator=(const BitReference& other);

        operator bool() const;

        bool operator~() const;
        bool operator&(const BitReference& other) const;
        bool operator|(const BitReference& other) const;
        bool operator^(const BitReference& other) const;
        bool operator&(bool value) const;
        bool operator|(bool value) const;
        bool operator^(bool value) const;

        BitReference& operator&=(bool value);
        BitReference& operator|=(bool value);
        BitReference& operator^=(bool value);
        BitReference& operator&=(const BitReference& other);
        BitReference& operator|=(const BitReference& other);
        BitReference& operator^=(const BitReference& other);

        bool operator==(bool value) const;
        bool operator==(const BitReference& other) const;
        bool operator!=(bool value) const;
        bool operator!=(const BitReference& other) const;

    private:
        unsigned char* ptr;
        int pos;
    };

    // Конструкторы / деструктор
    BitVector();
    BitVector(int size, bool value = false);
    BitVector(const char* str);
    BitVector(const BitVector& other);
    ~BitVector();

    // Основные методы
    int length() const;
    void swap(BitVector& other);

    void invert();
    void invert(int i);

    void set(int i, bool value = true);
    void set(int i, int k, bool value = true);
    void setAll(bool value = true);

    int weight() const;

    // Доступ к компоненте
    BitReference operator[](int i);
    bool operator[](int i) const;

    // Присваивание
    BitVector& operator=(const BitVector& other);

    // Составные побитовые операции
    BitVector& operator&=(const BitVector& other);
    BitVector& operator|=(const BitVector& other);
    BitVector& operator^=(const BitVector& other);

    // Сдвиги
    BitVector& operator<<=(int shift);
    BitVector& operator>>=(int shift);

    // Дружественные бинарные операции
    friend BitVector operator&(const BitVector& a, const BitVector& b);
    friend BitVector operator|(const BitVector& a, const BitVector& b);
    friend BitVector operator^(const BitVector& a, const BitVector& b);
    friend BitVector operator~(const BitVector& a);
    friend BitVector operator<<(const BitVector& a, int shift);
    friend BitVector operator>>(const BitVector& a, int shift);

    friend std::ostream& operator<<(std::ostream& os, const BitVector& a);
    friend std::istream& operator>>(std::istream& is, BitVector& a);

private:
    unsigned char* data;
    int count;
    int bytes;

    bool getBit(int i) const;
    void setBit(int i, bool value);
    void maskExtraBits();
};

#endif // BITVECTOR_H