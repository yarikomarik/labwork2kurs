#include "dynMs.h"

// Конструктор по умолчанию
DynMs::DynMs() {
    data = nullptr;
    count = 0;
    cap = 0;
}

// Конструктор из массива
DynMs::DynMs(const int* other, int n) {
    data = nullptr;
    count = 0;
    cap = 0;
    if (n > 0) {
        data = new int[n];
        for (int i = 0; i < n; i++) {
            data[i] = other[i];
        }
        count = n;
        cap = n;
    }
}

// Конструктор копирования
DynMs::DynMs(const DynMs& other) {
    data = nullptr;
    count = 0;
    cap = 0;
    if (other.count > 0) {
        data = new int[other.count];
        for (int i = 0; i < other.count; i++) {
            data[i] = other.data[i];
        }
        count = other.count;
        cap = other.count;
    }
}

// Деструктор
DynMs::~DynMs() {
    delete[] data;
}

// Получение размера
int DynMs::size() const {
    return count;
}

// Обмен содержимым
void DynMs::swap(DynMs& other) {
    int* pd = data; data = other.data; other.data = pd;
    int pc = count; count = other.count; other.count = pc;
    int pcap = cap; cap = other.cap; other.cap = pcap;
}

// Поиск элемента
int DynMs::find(int value) const {
    for (int i = 0; i < count; i++) {
        if (data[i] == value) return i;
    }
    return -1;
}

// Сортировка элементов
void DynMs::sort() {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - 1 - i; j++) {
            if (data[j] > data[j + 1]) {
                int t = data[j];
                data[j] = data[j + 1];
                data[j + 1] = t;
            }
        }
    }
}
// Поиск минимума
int DynMs::min() const {
    if (count == 0) return 0;  // на пустом — вернём 0, считать нечего
    int m = data[0];
    for (int i = 1; i < count; i++) {
        if (data[i] < m) m = data[i];
    }
    return m;
}

// Поиск максимума
int DynMs::max() const {
    if (count == 0) return 0;
    int m = data[0];
    for (int i = 1; i < count; i++) {
        if (data[i] > m) m = data[i];
    }
    return m;
}
// Вставка по индексу
bool DynMs::insert(int index, int value) {
    if (index < 0 || index > count) return false;
    if (count == cap) grow();

    for (int i = count; i > index; i--) {
        data[i] = data[i - 1];
    }
    data[index] = value;
    count++;
    return true;
}
// Вставка перед итератором
DynMs::iterator DynMs::insert(iterator pos, int value) {
    int index = (int)(pos - data);
    if (index < 0 || index > count) return end();
    insert(index, value);
    return data + index;
}

// Удаление по индексу
bool DynMs::removeAt(int index) {
    if (index < 0 || index >= count) return false;

    for (int i = index; i < count - 1; i++) {
        data[i] = data[i + 1];
    }
    count--;
    shrink();
    return true;
}

// Удаление по значению
bool DynMs::removeByValue(int value) {
    int idx = find(value);
    if (idx == -1) return false;
    return removeAt(idx);
}

// Расширение массива
void DynMs::grow() {
    int newCap;
    if (cap == 0) newCap = 1;
    else newCap = cap * 2;

    int* tmp = new int[newCap];
    for (int i = 0; i < count; i++) {
        tmp[i] = data[i];
    }
    delete[] data;
    data = tmp;
    cap = newCap;
}

// Сжатие массива
void DynMs::shrink() {
    if (count == 0) {
        delete[] data;
        data = nullptr;
        cap = 0;
        return;
    }
    if (count <= cap / 2) {
        int* tmp = new int[count];
        for (int i = 0; i < count; i++) {
            tmp[i] = data[i];
        }
        delete[] data;
        data = tmp;
        cap = count;
    }
}

// Оператор присваивания
DynMs& DynMs::operator=(const DynMs& other) {
    if (this == &other) return *this;
    DynMs tmp(other);
    swap(tmp);
    return *this;
}


// Удаление всех по значению
int DynMs::removeAllByValue(int value) {
    int removed = 0;
    for (int i = 0; i < count; ) {
        if (data[i] == value) {
            removeAt(i);   // после удаления i остаётся указывать на следующий
            removed++;
        } else {
            i++;
        }
    }
    return removed;
}

// Удаление по итератору
bool DynMs::removeByIterator(iterator pos) {
    int index = (int)(pos - data);
    return removeAt(index);
}

// Удаление диапазона
bool DynMs::removeRange(iterator first, iterator last) {
    int i1 = (int)(first - data);
    int i2 = (int)(last - data);
    if (i1 < 0 || i2 > count || i1 > i2) return false;
    if (i1 == i2) return true;  // пустой диапазон

    int n = i2 - i1;
    for (int i = i2; i < count; i++) {
        data[i - n] = data[i];
    }
    count -= n;
    shrink();
    return true;
}

// Доступ по индексу
int& DynMs::operator[](int index) { return data[index]; }
// Константный доступ
const int& DynMs::operator[](int index) const { return data[index]; }

// Добавление в конец
DynMs& DynMs::operator+=(int value) {
    insert(count, value);
    return *this;
}

// Добавление в конец (копия)
DynMs DynMs::operator+(int value) const {
    DynMs tmp(*this);
    tmp.insert(tmp.count, value);
    return tmp;
}

// Конкатенация
DynMs& DynMs::operator+=(const DynMs& other) {
    for (int i = 0; i < other.count; i++) {
        insert(count, other.data[i]);
    }
    return *this;
}

// Конкатенация (копия)
DynMs DynMs::operator+(const DynMs& other) const {
    DynMs tmp(*this);
    tmp += other;
    return tmp;
}

// Сравнение
bool DynMs::operator==(const DynMs& other) const {
    if (count != other.count) return false;
    for (int i = 0; i < count; i++) {
        if (data[i] != other.data[i]) return false;
    }
    return true;
}

// Неравенство
bool DynMs::operator!=(const DynMs& other) const {
    return !(*this == other);
}

// Начало (обычный)
DynMs::iterator DynMs::begin() { return data; }
// Конец (обычный)
DynMs::iterator DynMs::end() { return data + count; }
// Начало (константный)
DynMs::const_iterator DynMs::begin() const { return data; }
// Конец (константный)
DynMs::const_iterator DynMs::end() const { return data + count; }
// Начало (константный)
DynMs::const_iterator DynMs::cbegin() const { return data; }
// Конец (константный)
DynMs::const_iterator DynMs::cend() const { return data + count; }

// Вывод в поток
std::ostream& operator<<(std::ostream& os, const DynMs& a) {
    os << "[";
    for (int i = 0; i < a.count; i++) {
        os << a.data[i];
        if (i != a.count - 1) os << ", ";
    }
    os << "]";
    return os;
}

// Ввод из потока
std::istream& operator>>(std::istream& is, DynMs& a) {
    int n;
    std::cout << "enter n: ";
    if (!(is >> n)) { is.clear(); is.ignore(10000, '\n'); return is; }
    if (n < 0) return is;
    for (int i = 0; i < n; i++) {
        int x;
        std::cout << "enter element: ";
        if (!(is >> x)) { is.clear(); is.ignore(10000, '\n'); break; }
        a.insert(a.count, x);
    }
    return is;
}

