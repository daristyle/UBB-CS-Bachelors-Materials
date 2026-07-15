#include "FixedCapBiMap.h"
#include "FixedCapBiMapIterator.h"
#include <exception>


FixedCapBiMapIterator::FixedCapBiMapIterator(const FixedCapBiMap& d) : map(d), currentPos(0){}


void FixedCapBiMapIterator::first() {
	currentPos = 0;
}


void FixedCapBiMapIterator::next() {
	if(!this->valid()){
		throw std::exception();
	}
	++currentPos;
}


TElem FixedCapBiMapIterator::getCurrent(){
	if(!this->valid()){
		throw std::exception();
	}
	return this->map.elements[this->currentPos];
}


bool FixedCapBiMapIterator::valid() const {
	return this->currentPos < this->map.size();
}



