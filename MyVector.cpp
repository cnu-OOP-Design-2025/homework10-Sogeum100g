
#include "MyVector.h"
#include <stdexcept>

template<typename T>
void MyVector<T>::push_back(const T& val) {
    if (length == cap) {
        cap = (cap == 0)? 1 : cap * 2;
        T* newData = new T[cap];

        for (int i=0; i<length; i++) {
            newData[i] = data[i];
        }

        // 포인터 교체
        if (data != nullptr) delete[] data;
        data = newData;
    }
    data[length] = val;
    length++;
}

template<typename T>
void MyVector<T>::pop_back() {
    if (length > 0) {
        length--;
    }
}

template<typename T>
size_t MyVector<T>::size() const {
    return length;
}

template<typename T>
T& MyVector<T>::operator[](int i) {
    return data[i];
}



template<typename T>
bool MyVector<T>::operator==(const MyVector& other) const {
    if (length != other.length) { return false; }

    for (int i=0; i<length; i++) 
        if (data[i] != other.data[i]) { return false; }
    
    return true;
}

// 재정의한 == 이용
template<typename T>
bool MyVector<T>::operator!=(const MyVector& other) const {
    return !(*this == other);
}

template<typename T>
bool MyVector<T>::operator<(const MyVector& other) const {
    if (length > other.length) { return false; }
    else if (length < other.length) { return true; }

    for (int i=0; i<length; i++) 
        if (data[i] > other.data[i]) { return false; }
        else if (data[i] < other.data[i]) { return true; }
    
    // this == other
    return false;
}

// 재정의한 < 이용
template<typename T>
bool MyVector<T>::operator>(const MyVector& other) const {
    return (other < *this);
}

template<typename T>
bool MyVector<T>::operator<=(const MyVector& other) const {
    return !(other < *this);
}

template<typename T>
bool MyVector<T>::operator>=(const MyVector& other) const {
    return !(*this < other);
}


// Vector에 대한 반복자 : Iterator 내부

template<typename T>
T& MyVector<T>::Iterator::operator*() {
    return *ptr;
}

template<typename T>
typename MyVector<T>::Iterator& MyVector<T>::Iterator::operator++() {
    ptr++;
    return *this;
}

template<typename T>
typename MyVector<T>::Iterator& MyVector<T>::Iterator::operator--() {
    ptr--;
    return *this;
}
template<typename T>
typename MyVector<T>::Iterator MyVector<T>::Iterator::operator+(int n) const {
    return Iterator(ptr+n);
}

template<typename T>
typename MyVector<T>::Iterator MyVector<T>::Iterator::operator-(int n) const {
    return Iterator(ptr-n);
}

// 두 이터레이터가 같은 위치(메모리 주소)를 가리키는지 확인
template<typename T>
bool MyVector<T>::Iterator::operator==(const Iterator& other) const {
    return this->ptr == other.ptr;
}

template<typename T>
bool MyVector<T>::Iterator::operator!=(const Iterator& other) const {
    return this->ptr != other.ptr;
}

// 거리 계산
template<typename T>
int MyVector<T>::Iterator::operator-(const Iterator& other) const {
    return static_cast<int>(this->ptr - other.ptr); // size_t -> int 로 캐스팅
}

template<typename T>
typename MyVector<T>::Iterator MyVector<T>::begin() {
    return Iterator(data);
}
template<typename T>
typename MyVector<T>::Iterator MyVector<T>::end() {
    return Iterator(data+length);
}


template<typename T>
typename MyVector<T>::Iterator MyVector<T>::insert(Iterator pos, const T& value) {
    
    int n = (pos - Iterator(data));
    // 꽉 찼을때
    if (length == cap) {
        size_t newCap = (length == 0)? 1 : cap*=2;
        T* newData = new T[newCap];
        for (int i=0; i<n; i++) {
            newData[i] = data[i];
        }
        newData[n] = value;
        for (int i=n+1 ; i<length; i++) {
            newData[i+1] = data[i];
        }
        delete[] data;
        data = newData;
    }
    // 그냥 넣을 때
    else {
        for (int i=length; i>n; i--) {
            data[i] = data[i-1];
        }
        data[n] = value;
    }
    length++;
    return Iterator(data+n);
}

template<typename T>
typename MyVector<T>::Iterator MyVector<T>::erase(Iterator pos) {
    int n = pos - Iterator(data);

    for (int i=n; i<length-1; i++) {
        data[i] = data[i+1];
    }
    length--;
    return Iterator(data+n);
}

template<typename T>
void MyVector<T>::clear() {
    for (int i=0; i<length; i++) {
        data[i] = 0;
    }
    length = 0;
    cap = 0;
}

template<typename T>
T& MyVector<T>::at(size_t i) {
    if (i < length) {
        return data[i];
    }
    else {
        return data[0]; // 인덱스 벗어남
    }
}

template<typename T>
T& MyVector<T>::front() {
    return data[0];
}

template<typename T>
T& MyVector<T>::back() {
    return data[length-1];
}

template<typename T>
size_t MyVector<T>::capacity() const {
    return cap;
}

template<typename T>
bool MyVector<T>::empty() const {
    return length == 0;
}

