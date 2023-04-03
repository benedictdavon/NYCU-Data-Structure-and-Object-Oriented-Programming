#include "LinkedList.h"

LinkedList::LinkedList() {
	// Constructor
	Head = NULL;
}

void LinkedList::Push_back(int x) {
	// TODO : Insert a node to the end of the linked list, the node's value is x.
	ListNode* newNode = new ListNode(x);
	ListNode* temp = Head;

	if (Head == NULL) {
		Head = newNode;
		return;
	}

	while (temp->next != NULL)
		temp = temp->next;

	temp->next = newNode;
	length++;
}

void LinkedList::Push_front(int x) {
	if (!Head) {
		Head = new ListNode(x);
		return;
	}
	ListNode* temp = new ListNode(x);

	temp->next = Head;
	Head = temp;
	length++;
}


void LinkedList::Delete(int index) {
	// TODO : Remove the node with index ¡§index¡¨ in the linked list.
	int i = 0;
	ListNode* current = Head;

	if (current == NULL)
		return;

	if (index == 0) {
		Head = current->next;
		return;
	}

	for (int i = 0; current != NULL && i < index - 1; i++)
		current = current->next;

	if (current == NULL || current->next == NULL)
		return;
	ListNode* next = current->next->next;

	current->next = next;
}

void LinkedList::Print() {
	// TODO : Print all the elements in the linked list in order.
	ListNode* ptr = Head;

	while (ptr != NULL) {
		cout << ptr->val << " ";
		ptr = ptr->next;
	}
}

LinkedList::~LinkedList()
{
	while (Head) {
		ListNode* temp = Head;
		Head = Head->next;
		delete temp;
	}
}
