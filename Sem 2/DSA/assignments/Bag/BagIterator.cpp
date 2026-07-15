#include <exception>
#include "BagIterator.h"
#include "Bag.h"

using namespace std;

//theta(1)
BagIterator::BagIterator(const Bag& c): bag(c), pos(0), freq(0){}

//theta(1)
void BagIterator::first() {
	this->pos = this->bag.first;
	this->freq = 0;
}

/*
 * Best: theta(1)
 * Average: theta(1)
 * Worst: O(N)
 * Total: O(N)
 */
void BagIterator::next() {
	if(!valid()){
		throw exception();
	}
	++this->freq;
	if(this->freq >= this->bag.elements[this->pos]){
		this->freq = 0;
		do{
			++this->pos;
		}while(pos < this->bag.last && this->bag.elements[this->pos] == 0);
	}
}

//theta(1)
bool BagIterator::valid() const {
	return this->bag.first <= this->pos && this->pos < this->bag.last;
}


//theta(1)
TElem BagIterator::getCurrent() const
{
	if(!valid()){
		throw exception();
	}

	return this->pos + this->bag.minimum;
}
