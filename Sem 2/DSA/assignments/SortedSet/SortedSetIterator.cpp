#include "SortedSetIterator.h"
#include <exception>
#include <iostream>
#include <stdexcept>

using namespace std;

//theta(sizeSubtree(node))
void SortedSetIterator::inorderTraversal(SortedSet::BSTNode* node){
	if(node == nullptr) return;
	inorderTraversal(node->left);
	v[index++] = node->info;
	inorderTraversal(node->right);
}

//theta(N)
SortedSetIterator::SortedSetIterator(const SortedSet& m) : set(m), size(m.size())
{
	v = new TComp[size];
	index = 0;
	inorderTraversal(m.root);
	index = 0;
}

//theta(1)
void SortedSetIterator::first() {
	index = 0;
}

//theta(1)
void SortedSetIterator::next() {
	if(!valid()){
		throw invalid_argument("Iterator is not valid");
	}
	++index;
}


//TElem SortedSetIterator::getCurrent()
//theta(1)
TComp SortedSetIterator::getCurrent() const{
	if(!valid()){
		throw invalid_argument("Iterator is not valid");
	}
	return v[index];
}

//theta(1)
bool SortedSetIterator::valid() const {
	return index < size;
}

//theta(1)
SortedSetIterator::~SortedSetIterator(){
	delete[] v;
}
