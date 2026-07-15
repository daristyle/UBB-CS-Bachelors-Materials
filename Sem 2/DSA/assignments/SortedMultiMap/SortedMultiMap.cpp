#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>
#include <vector>
#include <exception>
#include <ranges>
using namespace std;

//theta(1)
SortedMultiMap::SortedMultiMap(Relation r): rel{r}, keyHead{NIL}, sz{0}{
}

//theta(1)
int SortedMultiMap::allocKeyNode(){
	int node;
	if(emptyKeys.empty()){
		node = key.size();
	}else{
		node = emptyKeys.back();
		emptyKeys.pop_back();
	}

	return node;
}

//theta(1)
int SortedMultiMap::allocValueNode(){
	int node;
	if(emptyValues.empty()){
		node = value.size();
	}else{
		node = emptyValues.back();
		emptyValues.pop_back();
	}

	return node;
}

/*
 * Best case:  theta(1)
 * Worst case:  theta(N)
 * Total: O(N)
 */
void SortedMultiMap::add(TKey c, TValue v) {
	int current;
	if(keyHead == NIL || (rel(c, key[keyHead]) && key[keyHead] != c)){
		int node = allocKeyNode();
		key[node] = c;
		head[node] = NIL;
		nextKey[node] = keyHead;
		prevKey[node] = NIL;
		if(keyHead != NIL){
			prevKey[keyHead] = node;
		}
		keyHead = node;
		current = node;
	}else if(key[keyHead] == c){
		current = keyHead;
	}else{
		current = keyHead;
		while(nextKey[current] != NIL && !rel(c, key[current])/*c>key[current]*/){
			current = nextKey[current];
		}

		if(key[current] != c){
			if(rel(c, key[current])){
				current = prevKey[current];
			}
			int node = allocKeyNode();
			key[node] = c;
			head[node] = NIL;
			nextKey[node] = nextKey[current];
			if(nextKey[current] != NIL){
				prevKey[nextKey[current]] = node;
			}
			prevKey[node] = current;
			nextKey[current] = node;

			current = node;
		}
	}

	int node = allocValueNode();
	value[node] = v;
	nextValue[node] = head[current];
	prevValue[node] = NIL;
	if(head[current] != NIL){
		prevValue[head[current]] = node;
	}
	head[current] = node;

	++sz;
}

/*
 * Best case:  theta(1)
 * Worst case:  theta(N)
 * Total: O(N)
 */
vector<TValue> SortedMultiMap::search(TKey c) const {
	if(keyHead == NIL){
		return vector<TValue>();
	}
	vector<TValue> v;
	int current = keyHead;
	while(nextKey.at(current) != NIL && !rel(c, key.at(current))/*c>key[current]*/){
		current = nextKey.at(current);
	}

	if(key.at(current) == c){
		current = head.at(current);
		while(current != NIL){
			v.push_back(value.at(current));
			current = nextValue.at(current);
		}
	}

	return v;
}

/*
 * Best case:  theta(1)
 * Worst case:  theta(N)
 * Total: O(N)
 */
bool SortedMultiMap::remove(TKey c, TValue v) {
	if(keyHead == NIL){
		return false;
	}
	int current = keyHead;
	while(nextKey[current] != NIL && !rel(c, key[current])/*c>key[current]*/){
		current = nextKey[current];
	}
	if(c != key[current]){
		return false;
	}

	int keyNode = current;
	current = head[current];
	if(value[current] == v){
		head[keyNode] = nextValue[current];
		if(nextValue[current] != NIL){
			prevValue[nextValue[current]] = NIL;
		}
		emptyValues.push_back(current);
		if(head[keyNode] == NIL){
			if(nextKey[keyNode] != NIL){
				prevKey[nextKey[keyNode]] = prevKey[keyNode];
			}
			if(prevKey[keyNode] != NIL){
				nextKey[prevKey[keyNode]] = nextKey[keyNode];
			}else{
				keyHead = nextKey[keyNode];
			}
			emptyKeys.push_back(keyNode);
		}
	}else{
		do{
			current = nextValue[current];
		}while(current != NIL && value[current] != v);

		if(current == NIL || value[current] != v){
			return false;
		}
		nextValue[prevValue[current]] = nextValue[current];
		if(nextValue[current] != NIL){
			prevValue[nextValue[current]] = prevValue[current];
		}
		emptyValues.push_back(current);
	}

	--sz;

	return true;
}

//theta(1)
int SortedMultiMap::size() const {
	return sz;
}

//theta(1)
bool SortedMultiMap::isEmpty() const {
	return sz == 0;
}

//theta(1)
SMMIterator SortedMultiMap::iterator() const {
	return SMMIterator(*this);
}

//theta(N)
SortedMultiMap::~SortedMultiMap() {
}