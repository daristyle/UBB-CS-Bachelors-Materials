#include "Matrix.h"
#include <exception>
#include <random>
using namespace std;

//theta(1)
Matrix::Node::Node(int _r, int _c, int _value, Node* _next): r(_r), c(_c), value(_value), next(_next){
}

//theta(1)
void Matrix::checkCoordinates(int row, int col) const{
	if(row < 0 || row >= rows || col < 0 || col >= columns) throw runtime_error("Invalid position");
}

//theta(1)
int Matrix::getRandomInt(TElem min, TElem max) {
	static std::random_device rd;
	static std::mt19937 gen(rd());

	std::uniform_int_distribution<TElem> distrib(min, max);
	return distrib(gen);
}

/*
 * Best case: theta(1)
 * Worst case: theta(sqrt(N))
 * Total: O(sqrt(N))
 */
bool Matrix::isPrime(int n){
	if(n <= 3) return n >= 2;
	if(n % 2 == 0 || n % 3 == 0) return false;
	for(int i = 5; i * i <= n; i += 6)
		if(n % i == 0 || n % (i + 2) == 0) return false;
	return true;
}

/*
 * Best case: theta(1)
 * Worst case: theta(sqrt(C)*log^2(C)) it will not happen
 * Total: O(sqrt(C)*log^2(C))
 */
int Matrix::getNextCapacity(){
	if(primeIndex >= NO_PRIMES){
		int newPrime = 2 * capacity + 1;
		while(!isPrime(newPrime)){
			newPrime += 2;
		}
		return newPrime;
	}else{
		return PRIMES[primeIndex++];
	}
}

/*
 * Best case: theta(1)
 * Worst case: theta(NoElements + C)
 * Total: O(NoElements + C)
 */
void Matrix::resize(){
	if((double)noElements / capacity < LOAD_FACTOR_THRESHOLD) return;

	int oldCapacity = capacity;
	capacity = getNextCapacity();
	a = getRandomInt(1, capacity - 1);
	b = getRandomInt(1, capacity - 1);
	Node** newHead = new Node*[capacity];
	for (int i = 0; i < capacity; i++){
		newHead[i] = nullptr;
	}
	for (int i = 0; i < oldCapacity; i++){
		Node* node = head[i], *temp;
		while(node != nullptr){
			temp = node->next;
			int key = hash(node->r, node->c);
			node->next = newHead[key];
			newHead[key] = node;
			node = temp;
		}
	}
	delete[] head;
	head = newHead;
}

//theta(1)
int Matrix::hash(int i, int j) const{
	return (a * i + b * j) % capacity;
}

//theta(1)
Matrix::Matrix(int nrLines, int nrCols): rows(nrLines), columns(nrCols), noElements(0){
	primeIndex = 0;

	capacity = getNextCapacity();
	head = new Node*[capacity];
	for (int i = 0; i < capacity; i++){
		head[i] = nullptr;
	}

	a = getRandomInt(1, capacity - 1);
	b = getRandomInt(1, capacity - 1);
}

//theta(1)
int Matrix::nrLines() const {
	return rows;
}

//theta(1)
int Matrix::nrColumns() const {
	return columns;
}

/*
 * Best case: theta(1)
 * Worst case: theta(NoElements)
 * Total: O(NoElements)
 */
TElem Matrix::element(int row, int col) const {
	checkCoordinates(row, col);
	TElem retVal = NULL_TELEM;
	int key = hash(row, col);
	Node *node = head[key];
	while(node != nullptr){
		if(node->r == row && node->c == col){
			retVal = node->value;
			break;
		}
		node = node->next;
	}

	return retVal;
}

/*
 * Best case: theta(1)
 * Worst case: theta(NoElements)
 * Total: O(NoElements)
 */
TElem Matrix::modify(int row, int col, TElem val) {
	checkCoordinates(row, col);

	TElem retVal = NULL_TELEM;
	int key = hash(row, col);
	Node *node = head[key], *prev = nullptr;
	while(node != nullptr){
		if(node->r == row && node->c == col){
			retVal = node->value;
			if(val != NULL_TELEM){
				node->value = val;
			}else{
				if(prev != nullptr){
					prev->next = node->next;
				}else{
					head[key] = node->next;
				}
				delete node;
				--noElements;
			}

			break;
		}
		prev = node;
		node = node->next;
	}

	if(node == nullptr && val != NULL_TELEM){
		node = new Node(row, col, val, head[key]);
		head[key] = node;
		++noElements;
		resize();
	}

	return retVal;
}

//theta(NoElements)
Matrix::~Matrix(){
	for(int i = 0; i < capacity; i++){
		Node* node = head[i];
		while(node != nullptr){
			Node* temp = node->next;
			delete node;
			node = temp;
		}
	}
	delete[] head;
}