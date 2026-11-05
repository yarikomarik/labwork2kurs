#include "BitVector.h"

// ================= BitReference =================

// Конструктор
BitVector::BitReference::BitReference(unsigned char* p, int pos) {
    ptr = p;
    this->pos = pos;
}

// Конструктор копирования
BitVector::BitReference::BitReference(const BitReference& other) {
    ptr = other.ptr;
    pos = other.pos;
}

// Присваивание значения
BitVector::BitReference& BitVector::BitReference::operator=(bool value) {
    if (value) *ptr |= (1 << pos);
    else       *ptr &= ~(1 << pos);
    return *this;
}

// Присваивание другого бита
BitVector::BitReference& BitVector::BitReference::operator=(const BitReference& other) {
    return operator=((bool)other);
}

// Конвертация в bool
BitVector::BitReference::operator bool() const {
    return (*ptr >> pos) & 1;
}

// Инверсия
bool BitVector::BitReference::operator~() const {
    return !(bool)(*this);
}

// Побитовые операции с другим битом
bool BitVector::BitReference::operator&(const BitReference& other) const {
    return (bool)(*this) && (bool)other;
}
bool BitVector::BitReference::operator|(const BitReference& other) const {
    return (bool)(*this) || (bool)other;
}
bool BitVector::BitReference::operator^(const BitReference& other) const {
    return (bool)(*this) != (bool)other;
}

// Побитовые операции с bool
bool BitVector::BitReference::operator&(bool value) const {
    return (bool)(*this) && value;
}
bool BitVector::BitReference::operator|(bool value) const {
    return (bool)(*this) || value;
}
bool BitVector::BitReference::operator^(bool value) const {
    return (bool)(*this) != value;
}

// Составные побитовые операции с bool
BitVector::BitReference& BitVector::BitReference::operator&=(bool value) {
    return operator=((bool)(*this) && value);
}
BitVector::BitReference& BitVector::BitReference::operator|=(bool value) {
    return operator=((bool)(*this) || value);
}
BitVector::BitReference& BitVector::BitReference::operator^=(bool value) {
    return operator=((bool)(*this) != value);
}

// Составные побитовые операции с битом
BitVector::BitReference& BitVector::BitReference::operator&=(const BitReference& other) {
    return operator&=((bool)other);
}
BitVector::BitReference& BitVector::BitReference::operator|=(const BitReference& other) {
    return operator|=((bool)other);
}
BitVector::BitReference& BitVector::BitReference::operator^=(const BitReference& other) {
    return operator^=((bool)other);
}

// Сравнение с bool
bool BitVector::BitReference::operator==(bool value) const {
    return (bool)(*this) == value;
}
bool BitVector::BitReference::operator!=(bool value) const {
    return !(*this == value);
}

// Сравнение с другим битом
bool BitVector::BitReference::operator==(const BitReference& other) const {
    return (bool)(*this) == (bool)other;
}
bool BitVector::BitReference::operator!=(const BitReference& other) const {
    return !(*this == other);
}

// ================= BitVector =================

// Конструктор по умолчанию
BitVector::BitVector() {
    data = nullptr;
    count = 0;
    bytes = 0;
}

// Конструктор с параметрами (размер и значение)
BitVector::BitVector(int size, bool value) {
    data = nullptr;
    count = 0;
    bytes = 0;
    if (size > 0) {
        count = size;
        bytes = (size + 7) / 8;
        data = new unsigned char[bytes];
        unsigned char fill = value ? 0xFF : 0x00;
        for (int i = 0; i < bytes; i++) {
            data[i] = fill;
        }
        maskExtraBits();
    }
}

// Конструктор из C-строки
BitVector::BitVector(const char* str) {
    data = nullptr;
    count = 0;
    bytes = 0;
    if (str == nullptr) return;

    int n = 0;
    while (str[n] == '0' || str[n] == '1') n++;

    if (n > 0) {
        count = n;
        bytes = (n + 7) / 8;
        data = new unsigned char[bytes];
        for (int i = 0; i < bytes; i++) data[i] = 0;
        for (int i = 0; i < count; i++) {
            if (str[i] == '1') setBit(i, true);
        }
    }
}

// Конструктор копирования
BitVector::BitVector(const BitVector& other) {
    data = nullptr;
    count = 0;
    bytes = 0;
    if (other.count > 0) {
        count = other.count;
        bytes = other.bytes;
        data = new unsigned char[bytes];
        for (int i = 0; i < bytes; i++) {
            data[i] = other.data[i];
        }
    }
}

// Деструктор
BitVector::~BitVector() {
    delete[] data;
}

// Получение длины
int BitVector::length() const {
    return count;
}

// Обмен содержимым
void BitVector::swap(BitVector& other) {
    unsigned char* pd = data; data = other.data; other.data = pd;
    int pc = count; count = other.count; other.count = pc;
    int pb = bytes; bytes = other.bytes; other.bytes = pb;
}

// Инверсия всех битов
void BitVector::invert() {
    for (int i = 0; i < bytes; i++) {
        data[i] = ~data[i];
    }
    maskExtraBits();
}

// Инверсия i-го бита
void BitVector::invert(int i) {
    data[i / 8] ^= (1 << (i % 8));
}

// Установка i-го бита
void BitVector::set(int i, bool value) {
    setBit(i, value);
}

// Установка k битов начиная с i-го
void BitVector::set(int i, int k, bool value) {
    for (int j = 0; j < k && (i + j) < count; j++) {
        setBit(i + j, value);
    }
}

// Установка всех битов
void BitVector::setAll(bool value) {
    unsigned char fill = value ? 0xFF : 0x00;
    for (int i = 0; i < bytes; i++) {
        data[i] = fill;
    }
    maskExtraBits();
}

// Вес вектора (количество единиц)
int BitVector::weight() const {
    int w = 0;
    for (int i = 0; i < bytes; i++) {
        unsigned char b = data[i];
        while (b) {
            w += b & 1;
            b >>= 1;
        }
    }
    return w;
}

// Доступ по индексу (с записью)
BitVector::BitReference BitVector::operator[](int i) {
    return BitReference(&data[i / 8], i % 8);
}

// Доступ по индексу (только чтение)
bool BitVector::operator[](int i) const {
    return getBit(i);
}

// Вспомогательные методы

// Обнуление незначащих битов последнего байта
void BitVector::maskExtraBits() {
    int extra = bytes * 8 - count;
    if (extra > 0 && data != nullptr) {
        data[bytes - 1] &= (0xFFu >> extra);
    }
}

// Чтение бита
bool BitVector::getBit(int i) const {
    return (data[i / 8] >> (i % 8)) & 1;
}

// Запись бита
void BitVector::setBit(int i, bool value) {
    if (value) data[i / 8] |= (1 << (i % 8));
    else       data[i / 8] &= ~(1 << (i % 8));
}

// Оператор присваивания
BitVector& BitVector::operator=(const BitVector& other) {
    if (this == &other) return *this;
    BitVector tmp(other);
    swap(tmp);
    return *this;
}

// Составное побитовое И
BitVector& BitVector::operator&=(const BitVector& other) {
    int n = (bytes < other.bytes) ? bytes : other.bytes;
    for (int i = 0; i < n; i++) {
        data[i] &= other.data[i];
    }
    for (int i = n; i < bytes; i++) {
        data[i] = 0;
    }
    maskExtraBits();
    return *this;
}

// Составное побитовое ИЛИ
BitVector& BitVector::operator|=(const BitVector& other) {
    int n = (bytes < other.bytes) ? bytes : other.bytes;
    for (int i = 0; i < n; i++) {
        data[i] |= other.data[i];
    }
    maskExtraBits();
    return *this;
}

// Составное исключающее ИЛИ
BitVector& BitVector::operator^=(const BitVector& other) {
    int n = (bytes < other.bytes) ? bytes : other.bytes;
    for (int i = 0; i < n; i++) {
        data[i] ^= other.data[i];
    }
    maskExtraBits();
    return *this;
}

// Сдвиг влево
BitVector& BitVector::operator<<=(int shift) {
    if (shift <= 0 || count == 0) return *this;
    if (shift >= count) { setAll(false); return *this; }

    int bs = shift / 8;
    int bsh = shift % 8;

    for (int j = bytes - 1; j >= 0; j--) {
        unsigned char r = 0;
        if (j - bs >= 0) {
            r = data[j - bs] << bsh;
            if (bsh > 0 && j - bs - 1 >= 0) {
                r |= data[j - bs - 1] >> (8 - bsh);
            }
        }
        data[j] = r;
    }
    maskExtraBits();
    return *this;
}

// Сдвиг вправо
BitVector& BitVector::operator>>=(int shift) {
    if (shift <= 0 || count == 0) return *this;
    if (shift >= count) { setAll(false); return *this; }

    int bs = shift / 8;
    int bsh = shift % 8;

    for (int j = 0; j < bytes; j++) {
        unsigned char r = 0;
        if (j + bs < bytes) {
            r = data[j + bs] >> bsh;
            if (bsh > 0 && j + bs + 1 < bytes) {
                r |= data[j + bs + 1] << (8 - bsh);
            }
        }
        data[j] = r;
    }
    maskExtraBits();
    return *this;
}

// Бинарное И
BitVector operator&(const BitVector& a, const BitVector& b) {
    int size = (a.count < b.count) ? a.count : b.count;
    BitVector r(size, false);
    int n = (a.bytes < b.bytes) ? a.bytes : b.bytes;
    for (int i = 0; i < n; i++) {
        r.data[i] = a.data[i] & b.data[i];
    }
    r.maskExtraBits();
    return r;
}

// Бинарное ИЛИ
BitVector operator|(const BitVector& a, const BitVector& b) {
    int size = (a.count < b.count) ? a.count : b.count;
    BitVector r(size, false);
    int n = (a.bytes < b.bytes) ? a.bytes : b.bytes;
    for (int i = 0; i < n; i++) {
        r.data[i] = a.data[i] | b.data[i];
    }
    r.maskExtraBits();
    return r;
}

// Бинарное исключающее ИЛИ
BitVector operator^(const BitVector& a, const BitVector& b) {
    int size = (a.count < b.count) ? a.count : b.count;
    BitVector r(size, false);
    int n = (a.bytes < b.bytes) ? a.bytes : b.bytes;
    for (int i = 0; i < n; i++) {
        r.data[i] = a.data[i] ^ b.data[i];
    }
    r.maskExtraBits();
    return r;
}

// Побитовая инверсия (копия)
BitVector operator~(const BitVector& a) {
    BitVector r(a);
    r.invert();
    return r;
}

// Сдвиг влево (копия)
BitVector operator<<(const BitVector& a, int shift) {
    BitVector r(a);
    r <<= shift;
    return r;
}

// Сдвиг вправо (копия)
BitVector operator>>(const BitVector& a, int shift) {
    BitVector r(a);
    r >>= shift;
    return r;
}

// Вывод в поток
std::ostream& operator<<(std::ostream& os, const BitVector& a) {
    for (int i = 0; i < a.count; i++) {
        os << (a.getBit(i) ? '1' : '0');
    }
    return os;
}

// Ввод из потока
std::istream& operator>>(std::istream& is, BitVector& a) {
    std::string s;
    if (is >> s) {
        BitVector tmp(s.c_str());
        a = tmp;
    }
    return is;
}