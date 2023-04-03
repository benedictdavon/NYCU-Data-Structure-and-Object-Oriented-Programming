#include "LinkedList.h"

LinkedList::LinkedList() {
	// Constructor
	Head = NULL;
}

void LinkedList::Push_back(int x) {
	// TODO : Insert a node to the end of the linked list, the node¡¦s value is x.
}

void LinkedList::Push_front(int x) {
	if (!Head) {
		Head = new ListNode(x);
		return;
	}
	ListNode* temp = new ListNode(x);

	temp->next = Head;
	Head = temp;
}

void LinkedList::Insert(int index, int x) {
	// TODO : Insert a node to the linked list at position ¡§index¡¨, the node's
	// value is x. The index of the first node in the linked list is 0.
}

void LinkedList::Delete(int index) {
	// TODO : Remove the node with index ¡§index¡¨ in the linked list.
}

void LinkedList::Reverse() {
	// TODO : Reverse the linked list.
	// Example :
	//
	// Original List : 1 -> 2 -> 3 -> 4 -> NULL
	// Updated List  : 4 -> 3 -> 2 -> 1 -> NULL
}

void LinkedList::Swap(int index_1, int index_2) {
	if (index_1 == index_2) return;

	// TODO : Swap two nodes in the linked list
	// Example : 
	// index_1 : 1   ,  index_2 : 3
	// 
	// Original List : 1 -> 2 -> 3 -> 4 -> NULL
	// Updated List  : 1 -> 4 -> 3 -> 2 -> NULL
}

void LinkedList::Print() {
	cout << "List: ";
	// TODO : Print all the elements in the linked list in order.
}

LinkedList::~LinkedList()
{
	while (Head) {
		ListNode* temp = Head;
		Head = Head->next;
		delete temp;
	}
}
