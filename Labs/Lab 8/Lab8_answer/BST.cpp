#include "BST.h"
#include<iostream>
#include<queue>
using namespace std;

void BST::insert(Node* insertNode) {
	//TODO: insert a node to BST
	Node* tempNode = new Node(insertNode->getValue());
	Node* current;
	Node* parent;

	// Check if root is null, if yes assign to root
	if (root == NULL) {
		root = tempNode;
		return;
	}
	// If not, assign to proper place
	current = root;
	parent = NULL;
	while (1) {
		parent = current;
		// If it's smaler, go to the left side value
		if (insertNode->getValue() < parent->getValue()) {
			current = current->getLchild();

			if (current == NULL) {
				parent->setLchild(insertNode);
				return;
			}
		}
		// If it's bigger, go to the right side value
		else if (insertNode->getValue() > parent->getValue()) {
			current = current->getRchild();

			if (current == NULL) {
				parent->setRchild(insertNode);
				return;
			}
		}
	}
	
}

void BST::InOrder_traversal(Node* root)
{
	if (root == NULL)
		return;
	InOrder_traversal(root->getLchild());
	cout << root->getValue() << " ";
	InOrder_traversal(root->getRchild());
	//TODO: Inorder traversal
}

// Get the height of the BST using recursive
int height(Node* node) {
	if (node == NULL)
		return 0;
	/*		50
			/\
		   5  10
		  /\   \
	   -10  7   17
				 \
				 24
	*/
	// Get the left side height and right side height
	int lHeight = height(node->getLchild());
	int rHeight = height(node->getRchild());

	// If left side is bigger, then the height of BST is the same as total child on the left side
	if (lHeight > rHeight)
		return(lHeight + 1);
	// Otherwise, the height of BST is the same as total child on the right side
	return(rHeight + 1);
}

void Current(Node* node, int level) {
	if (node == NULL)
		return;
	// Print the value
	if (level == 1) {
		cout << node->getValue() << " ";
		return;
	}
	// Value on the left side
	Current(node->getLchild(), level - 1);
	// Value on the right side
	Current(node->getRchild(), level - 1);
}

void BST::LevelOrder_traversal(Node* root)
{
	// TODO: Level order traversal
	// Loop from 1 to height of BST
	for (int i = 1; i <= height(root); i++) {
		Current(root, i);
	}
}


Node* BST::getRoot() {
	//TODO: return root of BST
	return root;
}