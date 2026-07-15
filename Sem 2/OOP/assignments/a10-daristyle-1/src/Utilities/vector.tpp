#pragma once
#include <stdexcept>

template <typename T>
vector<T>::vector(int _capacity): capacity(_capacity), sz(0){
    this->elem = new T[this->capacity];
};

template <typename T>
vector<T>::vector(const vector& other): capacity(other.capacity), sz(other.sz){
    this->elem = new T[this->capacity];
    for(int i = 0; i < this->sz; i++){
        this->elem[i] = other.elem[i];
    }
}

template <typename T>
vector<T>::~vector(){
    delete[] this->elem;
}

template <typename T>
void vector<T>::resize(){
    if(this->sz >= this->capacity){
        this->capacity *= 2;
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
void vector<T>::push_back(T value){
    this->elem[this->sz++] = value;
    this->resize();
}

template <typename T>
void vector<T>::pop_back(){
    --this->sz;
    this->resize();
}

template <typename T>
int vector<T>::size() const{
    return this->sz;
}

template <typename T>
bool vector<T>::empty() const{
    return !this->sz;
}

template <typename T>
T vector<T>::back() const{
    if(empty()){
        throw std::out_of_range("vector is empty");
    }
    return this->elem[this->sz - 1];
}

template <typename T>
T& vector<T>::operator[](int index) const{
    return this->elem[index];
}
