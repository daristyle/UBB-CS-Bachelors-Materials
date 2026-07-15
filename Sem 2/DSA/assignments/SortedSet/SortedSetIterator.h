#pragma once
#include "SortedSet.h"

//DO NOT CHANGE THIS PART
class SortedSetIterator
{
	friend class SortedSet;
private:
	SortedSetIterator(const SortedSet& m);

	const SortedSet& set;
	TComp* v;
	int size;
	int index;

	void inorderTraversal(SortedSet::BSTNode* node);

public:
	void first();
	void next();
	TComp getCurrent() const;
	//TElem getCurrent();
	bool valid() const;
	~SortedSetIterator();
};

