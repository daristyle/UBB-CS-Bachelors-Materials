#include "SMMIterator.h"
#include "SortedMultiMap.h"

//theta(1)
SMMIterator::SMMIterator(const SortedMultiMap& d) : map{d}{
	first();
}

//theta(1)
void SMMIterator::first(){
	this->keyNode = map.keyHead;
	if(this->keyNode != NIL){
		this->valueNode = map.head.at(this->keyNode);
	}else{
		this->valueNode = NIL;
	}
}

//theta(1)
void SMMIterator::next(){
	if(!valid()){
		throw exception();
	}
	this->valueNode = map.nextValue.at(this->valueNode);
	if(this->valueNode == NIL){
		this->keyNode = map.nextKey.at(this->keyNode);
		if(this->keyNode != NIL){
			this->valueNode = map.head.at(this->keyNode);
		}else{
			this->valueNode = NIL;
		}
	}
}

//theta(1)
bool SMMIterator::valid() const{
	return this->keyNode != NIL;
}

//theta(1)
TElem SMMIterator::getCurrent() const{
	if(!valid()){
		throw exception();
	}
	return {map.key.at(this->keyNode), map.value.at(this->valueNode)};
}