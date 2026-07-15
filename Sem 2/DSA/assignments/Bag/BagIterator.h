#include "Bag.h"

class BagIterator
{
	//DO NOT CHANGE THIS PART
	friend class Bag;
	
private:
	const Bag& bag;
	int pos, freq;

	//theta(1)
	BagIterator(const Bag& c);
public:
	//theta(1)
	void first();
	/*
	 * Best: theta(1)
	 * Average: theta(1)
	 * Worst: O(N)
	 * Total: O(N)
	 */
	void next();
	//theta(1)
	TElem getCurrent() const;
	//theta(1)
	bool valid() const;
};
