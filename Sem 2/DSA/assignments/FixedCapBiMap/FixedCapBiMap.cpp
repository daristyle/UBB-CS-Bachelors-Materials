#include "FixedCapBiMap.h"
#include "FixedCapBiMapIterator.h"
#include <exception>

FixedCapBiMap::FixedCapBiMap(int _capacity): capacity(_capacity), mapSize(0){
	this->elements = new TElem[_capacity];
}

FixedCapBiMap::~FixedCapBiMap() {
	delete[] this->elements;
}

bool FixedCapBiMap::add(TKey c, TValue v){
	if (this->isFull()){
		throw std::exception();
	}

	int count = 0, i = 0;
	while(i < this->mapSize && count < 2){
		count += this->elements[i++].first == c;
	}

	if(count < 2){
		this->elements[this->mapSize++] = TElem(c, v);
		return true;
	}

	return false;
}

ValuePair FixedCapBiMap::search(TKey c) const{
	ValuePair result = ValuePair(NULL_TVALUE, NULL_TVALUE);
	int i = 0;
	while(i < this->mapSize && result.second == NULL_TVALUE){
		if(this->elements[i].first == c){
			if(result.first == NULL_TVALUE){
				result.first = this->elements[i].second;
			}else{
				result.second = this->elements[i].second;
			}
		}
		++i;
	}

	return result;
}

bool FixedCapBiMap::remove(TKey c, TValue v){
	int i = 0;
	TElem el = TElem(c, v);
	while(i < this->mapSize && this->elements[i] != el) ++i;

	if(i >= this->mapSize) return false;

	this->elements[i] = this->elements[--this->mapSize];
	return true;
}

ValuePair FixedCapBiMap::removeAll(TKey c){
	ValuePair result = ValuePair(NULL_TVALUE, NULL_TVALUE);
	int i = 0;
	while(i < this->mapSize && result.second == NULL_TVALUE){
		if(this->elements[i].first == c){
			if(result.first == NULL_TVALUE){
				result.first = this->elements[i].second;
			}else{
				result.second = this->elements[i].second;
			}
			this->elements[i] = this->elements[--this->mapSize];
		}else{
			++i;
		}
	}

	return result;
}


int FixedCapBiMap::size() const {
	return this->mapSize;
}

bool FixedCapBiMap::isEmpty() const{
	return this->size() == 0;
}

bool FixedCapBiMap::isFull() const {
	return this->size() == this->capacity;
}

FixedCapBiMapIterator FixedCapBiMap::iterator() const {
	return FixedCapBiMapIterator(*this);
}



