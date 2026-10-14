#pragma once
#include <iostream>

template <typename T>
class DynMsT {
private:
    T* data;
    int count;
    int cap;

    void grow() {
        int newCap;
        if (cap == 0) newCap = 1;
        else newCap = cap * 2;

        T* tmp = new T[newCap];
        for (int i = 0; i < count; i++) {
            tmp[i] = data[i];
        }
        delete[] data;
        data = tmp;
        cap = newCap;
    }

    void shrink() {
        if (count == 0) {
            delete[] data;
            data = nullptr;
            cap = 0;
            return;
        }
        if (count <= cap / 2) {
            T* tmp = new T[count];
            for (int i = 0; i < count; i++) {
                tmp[i] = data[i];
            }
            delete[] data;
            data = tmp;
            cap = count;
        }
    }

public:
    DynMsT() {
        data = nullptr;
        count = 0;
        cap = 0;
    }

    DynMsT(const T* other, int n) {
        data = nullptr;
        count = 0;
        cap = 0;
        if (n > 0) {
            data = new T[n];
            for (int i = 0; i < n; i++) {
                data[i] = other[i];
            }
            count = n;
            cap = n;
        }
    }

    DynMsT(const DynMsT& other) {
        data = nullptr;
        count = 0;
        cap = 0;
        if (other.count > 0) {
            data = new T[other.count];
            for (int i = 0; i < other.count; i++) {
                data[i] = other.data[i];
            }
            count = other.count;
            cap = other.count;
        }
    }

    ~DynMsT() {
        delete[] data;
    }

    DynMsT& operator=(const DynMsT& other) {
        if (this == &other) return *this;
        DynMsT tmp(other);
        swap(tmp);
        return *this;
    }

    int size() const { return count; }
    int capacity() const { return cap; }

    void swap(DynMsT& other) {
        T* pd = data; data = other.data; other.data = pd;
        int pc = count; count = other.count; other.count = pc;
        int pcap = cap; cap = other.cap; other.cap = pcap;
    }

    int find(const T& value) const {
        for (int i = 0; i < count; i++) {
            if (data[i] == value) return i;
        }
        return -1;
    }

    void sort() {
        for (int i = 0; i < count - 1; i++) {
            for (int j = 0; j < count - 1 - i; j++) {
                if (data[j] > data[j + 1]) {
                    T t = data[j];
                    data[j] = data[j + 1];
                    data[j + 1] = t;
                }
            }
        }
    }

    bool insert(int index, const T& value) {
        if (index < 0 || index > count) return false;
        if (count == cap) grow();

        for (int i = count; i > index; i--) {
            data[i] = data[i - 1];
        }
        data[index] = value;
        count++;
        return true;
    }

    bool removeAt(int index) {
        if (index < 0 || index >= count) return false;

        for (int i = index; i < count - 1; i++) {
            data[i] = data[i + 1];
        }
        count--;
        shrink();
        return true;
    }

    bool removeByValue(const T& value) {
        int idx = find(value);
        if (idx == -1) return false;
        return removeAt(idx);
    }

    T& operator[](int index) { return data[index]; }
    const T& operator[](int index) const { return data[index]; }

    typedef T* iterator;
    typedef const T* const_iterator;
    iterator begin() { return data; }
    iterator end()   { return data + count; }
    const_iterator begin() const { return data; }
    const_iterator end()   const { return data + count; }
    const_iterator cbegin() const { return data; }
    const_iterator cend()   const { return data + count; }

    friend std::ostream& operator<<(std::ostream& os, const DynMsT& a) {
        os << "[";
        for (int i = 0; i < a.count; i++) {
            os << a.data[i];
            if (i != a.count - 1) os << ", ";
        }
        os << "]";
        return os;
    }

    friend std::istream& operator>>(std::istream& is, DynMsT& a) {
        int n;
        std::cout << "Сколько элементов? ";
        is >> n;
        for (int i = 0; i < n; i++) {
            T x;
            std::cout << "Элемент " << (i + 1) << ": ";
            is >> x;
            a.insert(a.count, x);
        }
        return is;
    }
};