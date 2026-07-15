#pragma once

template <typename T>
class vector{
private:
    T* elem;
    int sz;
    int capacity;

    /*
     * Resizes the vector to double/halve its capacity
     */
    void resize();

public:
    vector(int _capacity = 4);
    vector(const vector& other);
    ~vector();

    /*
     * Adds an element to the back of the vector
     */
    void push_back(T value);
    /*
     * Deletes the last element of the vector
     */
    void pop_back();

    /*
     * Returns the size of the vector
     */
    int size() const;
    /*
     * Returns true iff the vector is empty
     */
    bool empty() const;
    /*
     * Returns the last element of the vector or throws an exception if the vector is empty
     */
    T back() const;

    /*
     * Returns a reference to the element situated ath the position index
     */
    T& operator[](int index) const;
};

#include "vector.tpp"
