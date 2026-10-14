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
    DynMs();
    DynMs(const int* other, int n);
    DynMs(const DynMs& other);
    ~DynMs();

    DynMs& operator=(const DynMs& other);

    int size() const;

    void swap(DynMs& other);

    int find(int value) const;

    void sort();

    bool insert(int index, int value);
    bool removeAt(int index);
    bool removeByValue(int value);

    int& operator[](int index);
    const int& operator[](int index) const;

    typedef int* iterator;
    typedef const int* const_iterator;
    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;
    const_iterator cbegin() const;
    const_iterator cend() const;

    friend std::ostream& operator<<(std::ostream& os, const DynMs& a);
    friend std::istream& operator>>(std::istream& is, DynMs& a);
};