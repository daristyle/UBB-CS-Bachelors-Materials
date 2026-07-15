#pragma once
#include <stdexcept>

template <typename T>
dynamicarray<T>::dynamicarray(int _capacity): capacity(_capacity), sz(0){
    this->elem = new T[this->capacity];
};

template <typename T>
dynamicarray<T>::dynamicarray(const dynamicarray& other): capacity(other.capacity), sz(other.sz){
    this->elem = new T[this->capacity];
    for(int i = 0; i < this->sz; i++){
        this->elem[i] = other.elem[i];
    }
}

template <typename T>
dynamicarray<T>::~dynamicarray(){
    delete[] this->elem;
}

template <typename T>
void dynamicarray<T>::resize(){
    if(this->sz >= this->capacity){
        this->capacity = std::max(this->capacity * 2, this->sz);
    }else if(this->sz < this->capacity / 4){
        this->capacity /= 2;
    }else{
        return;
    }
    T* new_elem = new T[this->capacity];
    for(int i = 0; i < this->sz; i++){
        new_elem[i] = this->elem[i];
    }
    delete[] this->elem;
    this->elem = new_elem;
}

template <typename T>
void dynamicarray<T>::push_back(T value){
    this->elem[this->sz++] = value;
    this->resize();
}

template <typename T>
void dynamicarray<T>::pop_back(){
    --this->sz;
    this->resize();
}

template <typename T>
int dynamicarray<T>::size() const{
    return this->sz;
}

template <typename T>
bool dynamicarray<T>::empty() const{
    return !this->sz;
}

template <typename T>
T dynamicarray<T>::back() const{
    if(empty()){
        throw std::out_of_range("dynamicarray is empty");
    }
    return this->elem[this->sz - 1];
}

template <typename T>
T& dynamicarray<T>::operator[](int index){
    if(index >= this->sz){
        this->sz = index + 1;
        resize();
    }
    return this->elem[index];
}

template <typename T>
T dynamicarray<T>::at(int index) const{
    if(index < 0 || index >= this->sz){
        throw std::out_of_range( "dynamicarray::at: index out of range");
    }

    return this->elem[index];
}
