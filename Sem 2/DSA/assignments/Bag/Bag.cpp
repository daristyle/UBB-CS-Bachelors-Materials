#include "Bag.h"
#include "BagIterator.h"
#include <exception>
#include <iostream>
using namespace std;

/*
 * Best: theta(1)
 * Average: theta(N)
 * Worst: theta(N)
 * Total: O(N)
 */
void Bag::grow(TElem x){
	if(x < minimum){
		TElem* elems_new = new TElem[maximum - x + 1];
		for (int i = 0; i < maximum - x; ++i){
			elems_new[i] = 0;
		}
		for (int i = maximum - minimum; i >= 0; --i){
			elems_new[i + minimum - x] = this->elements[i];
		}
		first -= x - minimum;
		last -= x - minimum;
		minimum = x;
		delete[] this->elements;
		this->elements = elems_new;
	}else if(x > maximum){
		TElem* elems_new = new TElem[x - minimum + 1];
		for (int i = maximum - minimum + 1; i <= x - minimum; ++i){
			elems_new[i] = 0;
		}
		for (int i = 0; i <= maximum - minimum; ++i){
			elems_new[i] = this->elements[i];
		}
		maximum = x;
		delete[] this->elements;
		this->elements = elems_new;
	}
}


/*
 * Best: theta(1)
 * Average: theta(N)
 * Worst: theta(N)
 * Total: O(N)
 */
void Bag::shrink(){
	if(last <= first){
		delete[] this->elements;
		this->elements = nullptr;
		first = last = 0;
		return;
	}
	if(last - first + 1 < (maximum - minimum + 1) * 3 / 4){
		TElem* elems_new = new TElem[last - first];
		for (int i = first; i < last; ++i){
			elems_new[i - first] = this->elements[i];
		}
		delete[] this->elements;
		this->elements = elems_new;
		maximum = last - 1 + minimum;
		minimum = first + minimum;
		last = last - first;
		first = 0;
	}
}

//theta(1)
Bag::Bag(): sz(0), elements(nullptr), first(0), last(0), minimum(NULL_TELEM), maximum(NULL_TELEM){
}

/*
 * Best: theta(1)
 * Average: theta(1)
 * Worst: theta(N)
 * Total: O(N)
 */
void Bag::add(TElem elem) {
	if(size() == 0){
		minimum = maximum = elem;
		first = 0;
		last = 1;
		delete[] this->elements;
		this->elements = new TElem[1];
		this->elements[0] = 1;
		sz = 1;
		return;
	}

	grow(elem);
	int pos = elem - minimum;
	++this->elements[pos];
	++sz;
	if(first > pos){
		first = pos;
	}
	if(last < pos + 1){
		last = pos + 1;
	}
}

/*
 * Best: theta(1)
 * Average: theta(1)
 * Worst: theta(N)
 * Total: O(N)
 */
bool Bag::remove(TElem elem) {
	if(elem < minimum || elem > maximum || size() == 0){
		return false;
	}
	int pos = elem - minimum;
	if(!this->elements[pos]){
		return false;
	}

	--this->elements[pos];
	--sz;
	if(this->elements[pos] == 0){
		while(!elements[first] && first <= maximum - minimum + 1) ++first;
		while(!elements[last - 1] && last > 0) --last;
		shrink();
	}

	return true;
}

//theta(1)
bool Bag::search(TElem elem) const {
	return nrOccurrences(elem);
}

//theta(1)
int Bag::nrOccurrences(TElem elem) const {
	if(elem < minimum || elem > maximum || size() == 0){
		return 0;
	}

	return this->elements[elem - minimum];
}

//theta(1)
int Bag::size() const {
	return sz;
}

//theta(1)
bool Bag::isEmpty() const {
	return sz == 0;
}

//theta(1)
BagIterator Bag::iterator() const {
	return BagIterator(*this);
}

//theta(1)
Bag::~Bag() {
	delete[] this->elements;
}