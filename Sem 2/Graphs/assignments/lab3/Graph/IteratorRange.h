#pragma once

template <typename It>
class IteratorRange {
private:
    It b, e;
public:
    IteratorRange(It begin, It end);
    It begin() const;
    It end() const;
};

#include "IteratorRange.tpp"
