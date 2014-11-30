#ifndef __BST__
#define __BST__

#include<cstdlib>
namespace BST {

	struct Node {
		int key;
		Node *left, *right, *parent;
		Node(int k, Node* l = NULL, Node* r = NULL, Node* p = NULL);
	};

	void inorder(Node *root);
	void preorder(Node *root);
	Node* build123();
	void insert(Node *root, int data);
	Node* search(Node *root, int data);
	Node* subtreeSuccessor(Node *node);
	bool checkTree(Node *root);
	void deleteNode(Node *root, int data);
	


	// testing functions
	Node* createTestTree();
	void testInsert();
	void testSearch();
	void testDelete();
	void testCheckTree();
	
}

//void printTree(Node *root);
//void testPrintTree();


#endif