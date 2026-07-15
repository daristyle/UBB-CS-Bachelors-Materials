#pragma once

template <typename It>
IteratorRange<It>::IteratorRange(It begin, It end) : b(begin), e(end) {}

template <typename It>
It IteratorRange<It>::begin() const{
    return b;
}

template <typename It>
It IteratorRange<It>::end() const{
    return e;
}
