#ifndef ARRAY_H
#define ARRAY_H

// although Array is basically a vector<>, I'm calling it Array to minimize confusion with
// the mathematical concept of a vector, which we use when doing graphics programming
// I'm also adding a few methods like sort, insertAtIndex to simplify things and avoid the need
// to introduce iterators to first semester students
// another difference from vector is that size() returns a signed int, to avoid some other painful "gotchas"


#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <iterator>

//#pragma GCC diagnostic ignored "-Wsign-conversion"
//#pragma GCC diagnostic ignored "-Wsign-compare"
//#pragma GCC diagnostic ignored "-Wnarrowing"

using namespace std;

#ifdef DISABLE_ARRAY_SAFETY_CHECKS
constexpr bool enable_array_safety_checks = false;
#else
constexpr bool enable_array_safety_checks = true;
#endif

template<typename T>
class Array {
private:
    vector<T> elements;
public:
    class ArrayIterator : public iterator<random_access_iterator_tag, T> {
    public:
        using difference_type = int;
        using value_type = T;
        using pointer = T*;
        using reference = T&;
        using iterator_category = std::random_access_iterator_tag;
    private:
        Array* ptr;
        int idx;
    public:
        ArrayIterator(Array* ptr, int idx) : ptr{ptr}, idx{idx} { }

        void checkSameContainer(const ArrayIterator& other) const;

        ArrayIterator& operator+=(difference_type rhs);
        ArrayIterator& operator-=(difference_type rhs);

        reference operator*() const { return (*ptr)[idx]; }
        pointer operator->() const;
        reference operator[](difference_type rhs) const;

        difference_type operator-(const ArrayIterator& rhs) const;
        ArrayIterator operator+(difference_type rhs) const;
        ArrayIterator operator-(difference_type rhs) const;

        bool operator==(const ArrayIterator& rhs) const {
            if constexpr (enable_array_safety_checks) { checkSameContainer(rhs); }
            return idx == rhs.idx; }
        bool operator!=(const ArrayIterator& rhs) const {
            if constexpr (enable_array_safety_checks) { checkSameContainer(rhs); }
            return idx != rhs.idx; }
        bool operator>(const ArrayIterator& rhs) const  {
            if constexpr (enable_array_safety_checks) { checkSameContainer(rhs); }
            return idx > rhs.idx; }
        bool operator<(const ArrayIterator& rhs) const  {
            if constexpr (enable_array_safety_checks) { checkSameContainer(rhs); }
            return idx < rhs.idx; }
        bool operator>=(const ArrayIterator& rhs) const {
            if constexpr (enable_array_safety_checks) { checkSameContainer(rhs); }
            return idx >= rhs.idx; }
        bool operator<=(const ArrayIterator& rhs) const {
            if constexpr (enable_array_safety_checks) { checkSameContainer(rhs); }
            return idx <= rhs.idx; }

    public:

        ArrayIterator& operator++();
        ArrayIterator operator++(int);
        ArrayIterator& operator--();
        ArrayIterator operator--(int);
    };

public:
    Array();
    Array(initializer_list<T> items);
    T& operator[](int index);
    const T& operator[](int index) const;
    void append(T element);
    void push_back(T element) { append(element); }
    void removeAtIndex(int index);
    void insertAtIndex(int index, T element);
    int  size() const { return static_cast<int>(elements.size()); }
    void resize(int newSize, const T& value = T{});
    void clear();
    constexpr bool isIndexInRange(int index) const { return index >= 0 && index < elements.size(); }
    ArrayIterator begin() { return {this, 0}; }
    ArrayIterator end() { return {this, static_cast<int>(elements.size()) }; }
    const ArrayIterator begin() const { return {this, 0}; }
    const ArrayIterator end() const { return {this, elements.size()}; }
    void sort();
    T& front();
    T& back();
    const T& front() const;
    const T& back() const;
    bool empty() const { return elements.empty(); }
    vector<T>& asVector() { return elements; }
    const vector<T>& asVector() const { return elements; }
private:
    constexpr bool isIndexInRangeIncludingEnd(int index) const { return index >= 0 && index <= elements.size(); }
    inline void throwOnBadIndexIncludingEnd(int index) const;
    inline void throwOnBadIndex(int index) const;
    void throwIndexError(int index) const;
};


template<typename T>
void Array<T>::ArrayIterator::checkSameContainer(const ArrayIterator& other) const
{
    if (other.ptr != ptr) {
        throw std::logic_error("Can't mix iterators from different Array<T> containers!");
    }
}

template<typename T>
typename Array<T>::ArrayIterator Array<T>::ArrayIterator::operator++(int)
{
    Array<T>::ArrayIterator tmp = *this;
    idx++;
    if constexpr (enable_array_safety_checks) {
        if (!ptr->isIndexInRangeIncludingEnd(idx)) { ptr->throwIndexError(idx); }
    }
    return tmp;
}

template<typename T>
typename Array<T>::ArrayIterator &Array<T>::ArrayIterator::operator++()
{
    idx++;
    if constexpr (enable_array_safety_checks) {
        if (!ptr->isIndexInRangeIncludingEnd(idx)) {
            ptr->throwIndexError(idx);
        }
    }
    return *this;
}

template<typename T>
typename Array<T>::ArrayIterator Array<T>::ArrayIterator::operator--(int)
{
    Array<T>::ArrayIterator tmp = *this;
    idx--;
    if constexpr (enable_array_safety_checks) {
        if (!ptr->isIndexInRangeIncludingEnd(idx)) {
            ptr->throwIndexError(idx);
        }
    }
    return tmp;
}

template<typename T>
typename Array<T>::ArrayIterator &Array<T>::ArrayIterator::operator--()
{
    idx--;
    if constexpr (enable_array_safety_checks) {
        if (!ptr->isIndexInRangeIncludingEnd(idx)) {
            ptr->throwIndexError(idx);
        }
    }
    return *this;
}

template<typename T>
typename Array<T>::ArrayIterator::difference_type Array<T>::ArrayIterator::operator-(const ArrayIterator& rhs) const
{
    if constexpr (enable_array_safety_checks) {
        checkSameContainer(rhs);
    }
    return idx - rhs.idx;
}

template<typename T>
typename Array<T>::ArrayIterator Array<T>::ArrayIterator::operator+(difference_type rhs) const
{
    Array<T>::ArrayIterator ret = *this;
    ret.idx += rhs;
    if constexpr (enable_array_safety_checks) {
        if (!ret.ptr->isIndexInRangeIncludingEnd(ret.idx)) {
            ret.ptr->throwIndexError(ret.idx);
        }
    }
    return ret;
}

template<typename T>
typename Array<T>::ArrayIterator Array<T>::ArrayIterator::operator-(difference_type rhs) const
{
    Array<T>::ArrayIterator ret = *this;
    ret.idx -= rhs;
    if constexpr (enable_array_safety_checks) {
        if (!ret.ptr->isIndexInRangeIncludingEnd(ret.idx)) {
            ret.ptr->throwIndexError(ret.idx);
        }
    }
    return ret;
}

template<typename T>
typename Array<T>::ArrayIterator operator+(typename Array<T>::ArrayIterator::difference_type lhs, const typename Array<T>::ArrayIterator& rhs)
{
    typename Array<T>::ArrayIterator ret = rhs;
    ret.idx += lhs;
    if constexpr (enable_array_safety_checks) {
        if (!ret.ptr->isIndexInRangeIncludingEnd(ret.idx)) {
            ret.ptr->throwIndexError(ret.idx);
        }
    }
    return ret;
}

template<typename T>
typename Array<T>::ArrayIterator operator-(typename Array<T>::ArrayIterator::difference_type lhs, const typename Array<T>::ArrayIterator& rhs)
{
    typename Array<T>::ArrayIterator ret = rhs;
    ret.idx -= lhs;
    if constexpr (enable_array_safety_checks) {
        if (!ret.ptr->isIndexInRangeIncludingEnd(ret.idx)) {
            ret.ptr->throwIndexError(ret.idx);
        }
    }
    return ret;
}

template<typename T>
Array<T>::Array()
{
}

template<typename T>
Array<T>::Array(initializer_list<T> items)
    : elements{items}
{
}

template<typename T>
T &Array<T>::operator[](int index)
{
    if constexpr (enable_array_safety_checks) {
        if (!isIndexInRange(index)) {
            throwIndexError(index);
        }
    }
    return elements[index];
}

template<typename T>
const T &Array<T>::operator[](int index) const
{
    if constexpr (enable_array_safety_checks) {
        if (!isIndexInRange(index)) {
            throwIndexError(index);
        }
    }
    return elements[index];
}

template<typename T>
void Array<T>::append(T element)
{
    elements.push_back(element);
}

template<typename T>
void Array<T>::removeAtIndex(int index)
{
    if constexpr (enable_array_safety_checks) {
        if (!isIndexInRange(index)) {
            throwIndexError(index);
        }
    }
    elements.erase(elements.begin()+index);
}

template<typename T>
void Array<T>::insertAtIndex(int index, T element)
{
    if constexpr (enable_array_safety_checks) {
        if (!isIndexInRange(index)) {
            throwIndexError(index);
        }
    }
    elements.insert(elements.begin()+index, element);
}

template<typename T>
void Array<T>::resize(int newSize, const T &value)
{
    if constexpr (enable_array_safety_checks) {
        if (newSize < 0) {
            string msg = "Error:  Array cannot be resized to a negative size!";
            cout << msg << endl;
            throw invalid_argument(msg);
        }
    }
    elements.resize(newSize, value);
}

template<typename T>
void Array<T>::clear()
{
    elements.clear();
}



template<typename T>
void Array<T>::sort()
{
    std::sort(begin(), end());
}

template<typename T>
T &Array<T>::front()
{
    if constexpr (enable_array_safety_checks) {
        if (!isIndexInRange(0)) {
            throwIndexError(0);
        }
    }
    return elements.front();
}

template<typename T>
T &Array<T>::back()
{
    if constexpr (enable_array_safety_checks) {
        if (!isIndexInRange(0)) {
            throwIndexError(0);
        }
    }
    return elements.back();
}

template<typename T>
const T &Array<T>::front() const
{
    if constexpr (enable_array_safety_checks) {
        if (!isIndexInRange(0)) {
            throwIndexError(0);
        }
    }
    return elements.front();
}

template<typename T>
const T &Array<T>::back() const
{
    if constexpr (enable_array_safety_checks) {
        if (!isIndexInRange(0)) {
            throwIndexError(0);
        }
    }
    return elements.back();
}

template<typename T>
void Array<T>::throwOnBadIndexIncludingEnd(int index) const
{
    if (!isIndexInRangeIncludingEnd(index)) {
        throwIndexError(index);
    }
}

template<typename T>
void Array<T>::throwOnBadIndex(int index) const
{
    if (!isIndexInRange(index)) {
        throwIndexError(index);
    }
}

template<typename T>
void Array<T>::throwIndexError(int index) const
{
    string msg = "Error:  Array index " + to_string(index) + " out of range";
    if (elements.size() > 0) {
        msg.append(" (0, " + to_string(elements.size()-1) + ")");
    }
    else {
        msg.append(" (Array is empty!");
    }
    cerr << msg << endl;
    throw range_error(msg);
}



#endif // ARRAY_H
