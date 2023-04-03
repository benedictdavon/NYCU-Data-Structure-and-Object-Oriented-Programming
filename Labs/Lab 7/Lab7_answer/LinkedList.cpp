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
	ListNode* newNode = new ListNode(x);
	ListNode* temp = Head;

	if (index == 0) {
		Push_front(x);
	}
	else
	{
		for (int i = 0; temp != NULL && i < index - 1; i++)
			temp = temp->next;

		newNode->next = temp->next;
		temp->next = newNode;
	}


}

void LinkedList::Delete(int index) {
	// TODO : Remove the node with index ¡§index¡¨ in the linked list.
	int i = 0;
	ListNode* current = Head;

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

void LinkedList::Reverse() {
	// TODO : Reverse the linked list.
	// Example :
	//
	// Original List : 1 -> 2 -> 3 -> 4 -> NULL
	// Updated List  : 4 -> 3 -> 2 -> 1 -> NULL
	ListNode* current = Head;
	Head = NULL;

	//Rewrite the Head
	while (current != NULL) {
		Push_front(current->val);
		current = current->next;
	}
}

void LinkedList::Swap(int index_1, int index_2) {
	// TODO : Swap two nodes in the linked list
	// Example : 
	// index_1 : 1   ,  index_2 : 3
	// 
	// Original List : 1 -> 2 -> 3 -> 4 -> NULL
	// Updated List  : 1 -> 4 -> 3 -> 2 -> NULL
	if (index_1 == index_2) return;

	ListNode* firstTraverse = Head, *secondTraverse = Head;
	int num1 = 0, num2 = 0;
	/*int smaller = (index_1 < index_2) ? index_1 : index_2;
	int bigger = (index_1 > index_2) ? index_1 : index_2;*/
	for (int i = 0; firstTraverse != NULL; i++) {
		if (i == index_1) {
			num1 = firstTraverse->val;
		}
		else if (i == index_2) {
			num2 = firstTraverse->val;
		}
		firstTraverse = firstTraverse->next;
	}
	Head = NULL;
	//Rewrite the head
	for (int i = 0; secondTraverse != NULL; i++) {
		if (i == index_1) 
			Push_back(num2);
		else if (i == index_2) 
			Push_back(num1);
		else
			Push_back(secondTraverse->val);
		secondTraverse = secondTraverse->next;
	}
}

void LinkedList::Print() {
	cout << "List: ";
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
