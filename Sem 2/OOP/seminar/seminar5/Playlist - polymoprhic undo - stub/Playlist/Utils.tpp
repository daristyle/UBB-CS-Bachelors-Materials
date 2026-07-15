#include "Utils.h"

template<typename T>
void clear(std::stack<T>& s){
    while(!s.empty())
        s.pop();
}