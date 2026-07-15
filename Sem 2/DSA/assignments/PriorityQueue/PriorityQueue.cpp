#include "PriorityQueue.h"
#include <exception>
#include <stdexcept>
using namespace std;


//theta(1)
PriorityQueue::Node::Node(Element i, Node *n): info(i), next(n){
}

//theta(1)
PriorityQueue::PriorityQueue(Relation r): head(nullptr), rel(r), size(0){
}

/*
 * Best case: theta(1)
 * Worst case: theta(N)
 * Total: O(N)
 */
void PriorityQueue::push(TElem e, TPriority p) {
	if(isEmpty() || rel(p, head->info.second)){
		Node* newNode = new Node({e, p}, head);
		head = newNode;
		++size;
		return;
	}
	Node* current = this->head, *prev = head;
	while(current != nullptr && rel(current->info.second, p)){
		prev = current;
		current = current->next;
	}
	Node* newNode = new Node({e, p}, current);
	prev->next = newNode;
	++size;
}

//throws exception if the queue is empty
//theta(1)
Element PriorityQueue::top() const {
	if(isEmpty()){
		throw std::out_of_range("The priority queue is empty");
	}

	return head->info;
}

//theta(1)
Element PriorityQueue::pop() {
	Element ret_val = top();

	Node* temp = head->next;
	delete head;
	head = temp;

	--size;

	return ret_val;
}

//theta(1)
bool PriorityQueue::isEmpty() const {
	return !size;
}

//theta(N)
PriorityQueue::~PriorityQueue() {
	while(head != nullptr){
		Node* temp = head->next;
		delete head;
		head = temp;
	}
};

int PriorityQueue::count(TPriority p){
	Node* current = head;
	while(current != nullptr && (rel(current->info.second, p) && current->info.second != p)){
		current = current->next;
	}

	int cnt = 0;
	while(current != nullptr && current->info.second == p){
		current = current->next;
	}

	return cnt;
}