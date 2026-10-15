#pragma once
#include <iostream>

class DynMs {
private:
    int* data;
    int count;  // сколько элементов сейчас
    int cap;    // сколько влезает без расширения

    void grow();    // расширить
    void shrink();  // сжать

public:
    typedef int* iterator;
    typedef const int* const_iterator;

    DynMs();
    DynMs(const int* other, int n);
    DynMs(const DynMs& other);
    ~DynMs();

    DynMs& operator=(const DynMs& other);

    int size() const;

    void swap(DynMs& other);

    int find(int value) const;

    void sort();

    int min() const;
    int max() const;

    bool insert(int index, int value);
    iterator insert(iterator pos, int value);
    bool removeAt(int index);
    bool removeByValue(int value);
    bool removeByIterator(iterator pos);
    bool removeRange(iterator first, iterator last);
    int removeAllByValue(int value);

    int& operator[](int index);
    const int& operator[](int index) const;

    DynMs& operator+=(int value);
    DynMs operator+(int value) const;

    DynMs& operator+=(const DynMs& other);
    DynMs operator+(const DynMs& other) const;

    bool operator==(const DynMs& other) const;
    bool operator!=(const DynMs& other) const;
    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;
    const_iterator cbegin() const;
    const_iterator cend() const;

    friend std::ostream& operator<<(std::ostream& os, const DynMs& a);
    friend std::istream& operator>>(std::istream& is, DynMs& a);
};