#pragma once

template <typename T>
class dynamicarray{
private:
    T* elem;
    int sz;
    int capacity;

    /*
     * Resizes the dynamicarray to double/halve its capacity
     */
    void resize();

public:
    dynamicarray(int _capacity = 4);
    dynamicarray(const dynamicarray& other);
    ~dynamicarray();

    /*
     * Adds an element to the back of the dynamicarray
     */
    void push_back(T value);
    /*
     * Deletes the last element of the dynamicarray
     */
    void pop_back();

    /*
     * Returns the size of the dynamicarray
     */
    int size() const;
    /*
     * Returns true iff the dynamicarray is empty
     */
    bool empty() const;
    /*
     * Returns the last element of the dynamicarray or throws an exception if the dynamicarray is empty
     */
    T back() const;

    /*
     * Returns a reference to the element situated at the position index
     */
    T& operator[](int index);

    T at(int index) const;
};

#include "dynamicarray.tpp"
