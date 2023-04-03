#include "Queue.h"

void Queue::enqueue(int num) {
	List.Push_back(num);
}

void Queue::dequeue() {
	List.Delete(0);
}

void Queue::print() {
	cout << "The value in the queue: ";
	ListNode* ptr = List.Head;
	vector<int> temp;
	while (ptr != NULL) {
		temp.push_back(ptr->val);
		ptr = ptr->next;
	}
	for (int i = temp.size() - 1; i >= 0; i--)
		cout << temp[i] << " ";
	cout << endl;
}