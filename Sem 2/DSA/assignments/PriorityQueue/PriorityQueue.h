#pragma once
#include <vector>
#include <utility>

using namespace std;

//DO NOT CHANGE THIS PART
typedef int TElem;
typedef int TPriority;
typedef std::pair<TElem, TPriority> Element;
typedef bool (*Relation)(TPriority p1, TPriority p2);
#define NULL_TELEM pair<TElem, TPriority> (-11111,-11111)

class PriorityQueue {
private:
	struct Node{
		Element info;
		Node* next;

		//theta(1)
		Node(Element i, Node* n);
	};

	Node* head;
	Relation rel;
	int size;

public:
	//implicit constructor
	//theta(1)
	PriorityQueue(Relation r);

	//pushes an element with priority to the queue
	/*
	 * Best case: theta(1)
	 * Worst case: theta(N)
	 * Total: O(N)
	 */
	void push(TElem e, TPriority p);

	//returns the element with the highest priority with respect to the order relation
	//throws exception if the queue is empty
	//theta(1)
	Element top()  const;

	//removes and returns the element with the highest priority
	//throws exception if the queue is empty
	//theta(1)
	Element pop();

	//checks if the queue is empty
	//theta(1)
	bool isEmpty() const;

	//destructor
	//theta(N)
	~PriorityQueue();

	int count(TPriority p);;
};