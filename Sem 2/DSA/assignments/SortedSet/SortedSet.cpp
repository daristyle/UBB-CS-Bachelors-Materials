#include "SortedSet.h"
#include "SortedSetIterator.h"

int SortedSet::countLeaves(BSTNode *node){
	if(node == nullptr) return 0;
	if(node->left == nullptr && node->right == nullptr) return 1;
	return countLeaves(node->left) + countLeaves(node->right);
}

int SortedSet::f(){
	return countLeaves(root);
}

//theta(1)
SortedSet::BSTNode::BSTNode(int _info, BSTNode *_left, BSTNode *_right): info(_info), left(_left), right(_right){
}

//theta(1)
SortedSet::SortedSet(Relation r): relation(r), sz(0), root(nullptr) {
}

/*
 * Best case: theta(1)
 * Worst case: theta(sizeSubtree(node))
 * Total: O(sizeSubtree(node))
 */
bool SortedSet::add(BSTNode *node, BSTNode *parent, bool isLeft, TComp e){
	if(node == nullptr){
		node = new BSTNode(e);
		if(parent != nullptr){
			if(isLeft){
				parent->left = node;
			}else{
				parent->right = node;
			}
		}else{
			root = node;
		}
		sz++;
		return true;
	}
	if(node->info == e){
		return false;
	}
	if(relation(e, node->info)){
		return add(node->left, node, true, e);
	}
	return add(node->right, node, false, e);
}

/*
 * Best case: theta(1)
 * Worst case: theta(N)
 * Total: O(N)
 */
bool SortedSet::add(TComp elem){
	return add(root, nullptr, false, elem);
}

/*
 * Best case: theta(1)
 * Worst case: theta(sizeSubtree(node))
 * Total: O(sizeSubtree(node))
 */
bool SortedSet::remove(BSTNode *node, BSTNode *parent, TComp e){
	if(node == nullptr){
		return false;
	}
	if(node->info == e){
		if(node->left == nullptr || node->right == nullptr){
			BSTNode* temp = node->left ? node->left : node->right;
			if(parent != nullptr){
				if(parent->left == node){
					parent->left = temp;
				}else{
					parent->right = temp;
				}
			}else{
				root = temp;
			}
		}else{
			BSTNode* temp = node->left;
			parent = node;
			while(temp->right != nullptr){
				parent = temp;
				temp = temp->right;
			}
			node->info = temp->info;
			if(parent->left == temp){
				parent->left = nullptr;
			}else{
				parent->right = nullptr;
			}
			node = temp;
		}

		delete node;
		sz--;
		return true;
	}
	if(relation(e, node->info)){
		return remove(node->left, node,  e);
	}
	return remove(node->right, node, e);
}

/*
 * Best case: theta(1)
 * Worst case: theta(N)
 * Total: O(N)
 */
bool SortedSet::remove(TComp elem) {
	return remove(root, nullptr, elem);
}

/*
 * Best case: theta(1)
 * Worst case: theta(sizeSubtree(node))
 * Total: O(sizeSubtree(node))
 */
bool SortedSet::search(BSTNode *node, TComp e) const{
	if(node == nullptr){
			return false;
	}
	if(node->info == e){
		return true;
	}

	if(relation(e, node->info)){
		return search(node->left, e);
	}
	return search(node->right, e);
}

/*
 * Best case: theta(1)
 * Worst case: theta(N)
 * Total: O(N)
 */
bool SortedSet::search(TComp elem) const {
	return search(root, elem);
}

//theta(1)
int SortedSet::size() const {
	return sz;
}

//theta(1)
bool SortedSet::isEmpty() const {
	return !sz;
}

//theta(N)
SortedSetIterator SortedSet::iterator() const {
	return SortedSetIterator(*this);
}

////theta(sizeSubtree(node))
void SortedSet::deallocateSubtree(BSTNode *node){
	if(node == nullptr) return;
	deallocateSubtree(node->left);
	deallocateSubtree(node->right);
	delete node;
}

//theta(N)
SortedSet::~SortedSet() {
	deallocateSubtree(root);
}