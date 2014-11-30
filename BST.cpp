#include "BST.h"
#include <iostream>
#include <cassert>
#include <cmath>
#include <algorithm>
using namespace std;
using namespace BST;

namespace BST {
	Node::Node(int k, Node* l, Node* r, Node* p) :key(k), left(l), right(r), parent(p){}

	void inorder(Node *root) {
		if (root != NULL) {
			inorder(root->left);
			cout << root->key << " ";
			inorder(root->right);
		}
	}

	void preorder(Node *root) {
		if (root != NULL) {
			cout << root->key << " ";
			preorder(root->left);
			preorder(root->right);
		}
	}

	Node* build123() {
		Node *root = new Node(2);
		Node *left = new Node(1);
		Node *right = new Node(3);
		root->left = left;
		left->parent = root;
		root->right = right;
		right->parent = root;
		return root;
	}

	void insert(Node **root, int data) {
		Node *newNode = new Node(data);
		if (*root == NULL) {
			*root = newNode;
			return;
		}
		Node *node = *root;
		if (data < node->key) {
			if (node->left == NULL) {
				node->left = newNode;
				newNode->parent = node;
			}
			else
				insert(&(node->left), data);
		}
		else {
			if (node->right == NULL) {
				node->right = newNode;
				newNode->parent = node;
			}
			else
				insert(&(node->right), data);
		}
	}

	Node* search(Node *root, int data) {
		if (root == NULL) return NULL;
		if (data < root->key) return search(root->left, data);
		else if (data > root->key) return search(root->right, data);
		else return root;
	}

	Node* subtreeSuccessor(Node *node) {
		Node *successor = node->right;
		if (successor == NULL) return successor;
		while (successor->left != NULL)
			successor = successor->left;
		return successor;
	}

	Node* subtreePredecessor(Node *node) {
		Node *pre = node->left;
		if (pre == NULL) return pre;
		while (pre->right != NULL)
			pre = pre->right;
		return pre;
	}

	bool checkTree(Node *root) {
		if (root == NULL) return true;	// if tree is NULL

		bool isTree = true;;
		if (root->left) {
			if (root->left->parent != root) return false;
			if (root->left->key >= root->key) return false;
			if (!checkTree(root->left)) return false;
		}
		if (root->right) {
			if (root->right->parent != root) return false;
			if (root->right->key < root->key) return false;
			if (!checkTree(root->right)) return false;
		}
		return true;
	}

	void deleteNode(Node **proot, int data) {
		Node *root = *proot;
		Node *todelete = search(root, data);
		if (todelete == NULL) // Node not found
			return;

		// case where node to be deleted does not have any children
		if (todelete->left == NULL && todelete->right == NULL) {
			//not root node
			if (todelete != root) {
				Node *father = todelete->parent;
				if (father->left == todelete)
					father->left = NULL;
				else father->right = NULL;		
				delete todelete;
			}
			// root node
			else {	
				delete todelete;
				*proot = NULL;
			}
		}

		else if (todelete->right != NULL) { // right subtree exists
			Node *succ = subtreeSuccessor(todelete);

			if (todelete->parent != NULL) {
				if (todelete->parent->left == todelete)
					todelete->parent->left = succ;
				else
					todelete->parent->right = succ;
			}
			else {
				*proot = succ;
			}

			if (succ->parent == todelete) { // succ is direct child (todelete->right == succ)
				succ->parent = todelete->parent;
				succ->left = todelete->left;
				if (todelete->left)
					todelete->left->parent = succ;				
			}
			else { // succ is not a direct child
				succ->parent->left = succ->right;
				if (succ->right != NULL)
					succ->right->parent = succ->parent;
				succ->parent = todelete->parent;
				succ->left = todelete->left;
				succ->right = todelete->right;
				if (todelete->left != NULL)
					todelete->left->parent = succ;
				todelete->right->parent = succ;
			}
			delete todelete;
		}

		else {	// only left subtree  exists
			// if todelete is root
			if (todelete->parent == NULL) {
				*proot = todelete->left;
				todelete->left->parent = NULL;			
			}
			else {
				Node *replacement = todelete->left;
				if (todelete->parent->left == todelete)
					todelete->parent->left = replacement;
				else
					todelete->parent->right = replacement;

				replacement->parent = todelete->parent;
			}
			delete todelete;
		}
	}

	void testDelete() {
		//Node *root = NULL;
		//insert(&root, 10);
		//deleteNode(&root, 10);
		//assert(checkTree(root));

		//Node *root1 = NULL;
		//insert(&root1, 10);
		//insert(&root1, 20);
		//insert(&root1, 5);
		//insert(&root1, 6);
		//deleteNode(&root1, 6);
		//assert(checkTree(root1));

		//Node *root2 = NULL;
		//insert(&root2, 20);
		//insert(&root2, 10);
		//insert(&root2, 30);
		//deleteNode(&root2, 20);
		//assert(checkTree(root2));

		//Node *root3 = NULL;
		//insert(&root3, 20);
		//insert(&root3, 10);
		//insert(&root3, 30);
		//insert(&root3, 25);
		//deleteNode(&root3, 20);
		//assert(checkTree(root3));

		Node *root4 = NULL;
		insert(&root4, 50);
		insert(&root4, 20);
		insert(&root4, 80);
		insert(&root4, 10);
		insert(&root4, 30);
		insert(&root4, 70);
		insert(&root4, 90);
		insert(&root4, 25);
		insert(&root4, 40);
		insert(&root4, 60);
		insert(&root4, 75);
		deleteNode(&root4, 50);
		assert(checkTree(root4));
		deleteNode(&root4, 20);
		assert(checkTree(root4));
		deleteNode(&root4, 90);
		assert(checkTree(root4));
		deleteNode(&root4, 80);
		assert(checkTree(root4));
		deleteNode(&root4, 30);
		assert(checkTree(root4));
		deleteNode(&root4, 25);
		assert(checkTree(root4));
		deleteNode(&root4, 40);
		assert(checkTree(root4));
		deleteNode(&root4, 60);
		assert(checkTree(root4));
		deleteNode(&root4, 75);
		assert(checkTree(root4));
		deleteNode(&root4, 70);
		assert(checkTree(root4));
		deleteNode(&root4, 10);
		assert(checkTree(root4));
	}


	int getHeight(Node *root) {
		if (root == NULL) return 0;
		return std::max(getHeight(root->left), getHeight(root->right)) + 1;
	}




	// Testing functions

	Node* createTestTree() {
		Node *root = NULL;
		insert(&root, 3);
		insert(&root, 5);
		insert(&root, 7);
		insert(&root, 2);
		insert(&root, 1);
		insert(&root, 4);
		insert(&root, 3);

		return root;
	}

	void testInsert() {
		Node *root = createTestTree();
		//should be: 1 2 3 3 4 5 7
		inorder(root);
		cout << endl;
		//should be: 3 2 1 5 4 3 7
		preorder(root);
	}

	void testSearch() {
		Node *root = createTestTree();
		cout << (search(root, 3) != NULL) << " "
			<< (search(root, 4) != NULL) << " "
			<< (search(root, 10) == NULL) << endl;
	}



	void testCheckTree() {
		Node *root = NULL;
		assert(checkTree(root));
		
		root = new Node(10);
		assert(checkTree(root));

		root->left = new Node(5);
		root->left->parent = root;
		assert(checkTree(root));
	}

}


/*void printTree(Node *root) {
	int treeHeight = getHeight(root);
	int reqdRows = pow(2, treeHeight - 1) - 1 + treeHeight;
	cout << "Required rows: " << reqdRows << endl;
}

void testPrintTree() {
	Node *root = NULL;
	insert(&root, 5);
	insert(&root, 3);
	insert(&root, 7);
	insert(&root, 1);
	insert(&root, 4);
	insert(&root, 6);
	insert(&root, 8);
	insert(&root, 9);
	printTree(root);
}*/
