#pragma once
//DO NOT INCLUDE BAGITERATOR


//DO NOT CHANGE THIS PART
//deleted the ; at the end of NULL_TELEM
#define NULL_TELEM -111111
typedef int TElem;
class BagIterator; 
class Bag {

private:
	TElem* elements;
	TElem minimum, maximum;
	int first, last;
	int sz;

	
	/*
	 * Best: theta(1)
	 * Average: theta(N)
	 * Worst: theta(N)
	 * Total: O(N)
	 */
	void grow(TElem x);
	/*
	 * Best: theta(1)
	 * Average: theta(N)
	 * Worst: theta(N)
	 * Total: O(N)
	 */
	void shrink();

	//DO NOT CHANGE THIS PART
	friend class BagIterator;
public:
	//constructor
	//theta(1)
	Bag();

	//adds an element to the bag
	/*
	 * Best: theta(1)
	 * Average: theta(1)
	 * Worst: theta(N)
	 * Total: O(N)
	 */
	void add(TElem e);

	//removes one occurence of an element from a bag
	//returns true if an element was removed, false otherwise (if e was not part of the bag)
	/*
	 * Best: theta(1)
	 * Average: theta(1)
	 * Worst: theta(N)
	 * Total: O(N)
	 */
	bool remove(TElem e);

	//checks if an element appears is the bag
	//theta(1)
	bool search(TElem e) const;

	//returns the number of occurrences for an element in the bag
	//theta(1)
	int nrOccurrences(TElem e) const;

	//returns the number of elements from the bag
	//theta(1)

	int size() const;

	//returns an iterator for this bag
	//theta(1)
	BagIterator iterator() const;

	//checks if the bag is empty
	//theta(1)
	bool isEmpty() const;

	//destructor
	//theta(1)
	~Bag();
};