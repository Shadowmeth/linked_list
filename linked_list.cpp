#include <iostream>
#include <cassert>
using namespace std;

struct Node
{
	int data;
	Node* next;
};

struct List
{
	int sz; // size of the linked list
	Node* first, * last;
};

// PROTOTYPES
List* newList();
Node* newNode(int);
Node* getNode(List*, int);
Node* nextNode(Node*);
Node* previousNode(List*, Node*);
bool isLastNode(Node*);
int size(List*);
int indexOf(List*, int);
bool isEmpty(List*);
void insertAtBeginning(List*, int);
void insertAtEnd(List*, int);
void add(List*, int, int);
void display(List*);
List* reversedList(List*);
bool listEqual(List*, List*);
bool isPalindrome(List*);
int frequency(List*, int);
void displayFrequencies(List*);
void reverseDisplay(List*);
void deleteNodes(List*);
void deleteList(List**);
void remove(List*, int);
List* duplicate(List*);
void deleteSmallest(List*);
int lastIndexOf(List*, int);
void deleteDuplicates(List*);
void printMiddle(List*);
List* pairList(List*, List*);
void swapNodes(List*, int, int);
void swapFirstAndLastNode(List*);
void swapFirstWithKNode(List*, int);
void swapLastWithKNode(List*, int);
Node* getIndexBasedNode(List*, int);
void swapNonConsecutivePAndK(List*, int, int);
void swapConsecutivePAndK(List*, int, int);
void swapKthNodes(List*, int);
void addListToSelf(List*);
void swapAllNodes(List*);
void reverseInGroupedSize(List*, int);
void pairWiseSwapping(List*);

Node* getIndexBasedNode(List* l, int k)
{
	Node* n = l->first;
	for (int i = 0; i < k; i++) {
		n = n->next;
	}
	return n;
}

// return a new heap allocated linked list
List* newList()
{
	List* l = new List;
	l->first = l->last = NULL;
	l->sz = 0;

	return l;
}

// return a new heap allocated node
Node* newNode(int x)
{
	Node* n = new Node;
	n->data = x;
	n->next = NULL;

	return n;
}

// return the Node pointer containing x, if x doesn't exist in linked list return NULL
Node* getNode(List* l, int x)
{
	Node* temp;
	for (temp = l->first; temp && temp->data != x; temp = temp->next) {
		; // do nothing
	}

	return temp; // temp automatically contains the address or NULL
}

// return the next node given the Node n
// this will return an address of a node if it isn't the last node of the linked list
// if n is the last node in the linked list it'll return NULL
// remember to check the return value of this function!!
Node* nextNode(Node* n)
{
	return (n->next);
}

// return the previous node given the Node n
// if n itself is the first node we return the first node
Node* previousNode(List* l, Node* n)
{
	Node* prev, * curr;
	prev = curr = l->first;

	while (curr && curr != n) {
		prev = curr;
		curr = curr->next;
	}

	// if the node n exist in the linked list the address of previous node will be returned
	// if the node n doesn't exist in the linked list, NULL will be returned
	// remember to check return value of this function!!
	return prev; // REMEMBER WE NEED PREVIOUS!! NOT CURRENT, there was a logic error here before
}

// return true if the node n is the last node of the linked list
// we know it's last node of a linked list when it's next field is NULL :)
bool isLastNode(Node* n)
{
	return (n->next == NULL);
}

// return the size of the linked list
int size(List* l)
{
	return l->sz;
}

// search x in linked list, if it exists return the index, it it doesn't exists return -1
int indexOf(List* l, int x)
{
	int index = 0;
	Node* temp;
	for (temp = l->first; temp && temp->data != x; temp = temp->next) {
		index++;
	}

	// if temp contains NULl we reached end of list without finding x
	// if it contains some address then we found the element
	return (temp == NULL) ? -1 : index;
}

// return last index of x in the linked list, -1 otherwise
int lastIndexOf(List* l, int x)
{
	int index = -1;
	Node* curr = l->first;
	int i = 0;
	while (curr) {
		if (curr->data == x) {
			index = i;
		}
		i++;
		curr = curr->next;
	}

	return index;
}

// return true if list is empty
bool isEmpty(List* l)
{
	return (l->first == NULL) && (l->last == NULL);
}

void insertAtBeginning(List* l, int x)
{
	Node* n = newNode(x);
	if (isEmpty(l)) {
		// list is empty
		l->first = l->last = n;
	}
	else {
		// list is not empty
		n->next = l->first; // point the new node to the first node
		l->first = n; // and update the first pointer of the linked list
	}

	l->sz++; // we gotta update the size of the linked list
			// irrespective of how the pointers were changed since we added a new element

}

void insertAtEnd(List* l, int x)
{
	Node* n = newNode(x);
	if (isEmpty(l)) {
		// list is empty
		l->first = l->last = n;
	}
	else {
		// list is not empty
		l->last->next = n; // make the last node point to the newly created node
		l->last = n; // and update the last pointer of the linked list
	}

	l->sz++; // we gotta update the size of the linked list
			// irrespective of how the pointers were changed since we added a new element
}

void add(List* l, int index, int item)
{
	// if the index is greater than the size of linked list we can't do anything
	if (index > l->sz - 1) {
		return; // do nothing, we received invalid index
	}
	if (index < 0) {
		return; // index can't be negative either :)
	}

	Node* curr = l->first;

	for (int i = 0; i < index - 1; curr = curr->next, i++) {
		; // do nothing
	}

	Node* prev = previousNode(l, curr);
	Node* temp = newNode(item);
	temp->next = prev->next;
	prev->next = temp;
	l->sz++;
}

void remove(List* l, int index)
{
	// if the index is greater than the size of linked list we can't do anything 
	if (index > l->sz - 1) {
		return; // do nothing, we received invalid index
	}
	if (index < 0) {
		return; // index can't be negative either :)
	}

	Node* curr = l->first;
	for (int i = 0; i < index; curr = curr->next, i++) {
		; // do nothing
	}

	// curr now contains the node to be deleted
	Node* prev = previousNode(l, curr);
	// THERE ARE 2 special cases here, if index is 0 or the index is l->sz - 1
	// we will need to update the first and last pointers appropriately
	Node* temp = curr;
	
	if (curr == l->first) {
		temp = l->first;
		l->first = l->first->next;
	}
	else if (curr == l->last) {
		temp = l->last;
		l->last = previousNode(l, l->last);
		l->last->next = NULL;
	}
	else {
		prev->next = curr->next;
	}

	delete temp;
	l->sz--; // DON'T FORGET TO UPDATE THE SIZE!!!
}

List* duplicate(List* l)
{
	List* duplicate = newList();
	Node* curr = l->first;
	while (curr) {
		insertAtEnd(duplicate, curr->data);
		curr = curr->next;
	}

	return duplicate;
}

// display the linked list
void display(List* l)
{
	for (Node* temp = l->first; temp; temp = temp->next) {
		cout << temp->data << " -> ";
	}

	cout << "NULL" << endl;
}

// this function returns a new list that is reversed
List* reversedList(List* l)
{
	List* reverse = newList();
	// 5 -> 7 -> 17 -> 13 -> 11
	// 11 -> 13 -> 17 -> 7 -> 5
	Node* temp = l->first; // original list that we want to reverse
	while (temp) {
		insertAtBeginning(reverse, temp->data);
		temp = temp->next;
	}

	return reverse;
}

// we want to check if the linked lists are equal or not
bool listEqual(List* l1, List* l2)
{
	if (l1->sz != l2->sz) {
		return false;
	}

	Node* temp1 = l1->first;
	Node* temp2 = l2->first;
	while (temp1 && temp2) {
		if (temp1->data != temp2->data) {
			return false;
		}
		temp1 = temp1->next;
		temp2 = temp2->next;
	}

	return true;
}

// return whether the list is a palindrome or not
bool isPalindrome(List* l)
{
	List* reversed = reversedList(l);

	bool isLPalindrome = listEqual(l, reversed);
	deleteList(&reversed);

	return isLPalindrome;
}

int frequency(List* l, int element)
{
	int count = 0;
	Node* temp = l->first;
	while (temp) {
		if (temp->data == element) {
			count++;
		}
		temp = temp->next;
	}
	return count;
}

void displayFrequencies(List* l)
{
	// we can maintain a new linked list
	// one that contains the elements whose frequency has been displayed
	List* displayed = newList();
	Node* temp = l->first;
	while (temp) {
		int d = temp->data;
		if (indexOf(displayed, d) == -1) {
			// frequency of d hasn't been printed yet
			cout << "frequency(" << d << ") = " << frequency(l, d) << endl;
			// d has been printed, now add it to the displayed list
			insertAtEnd(displayed, d);
		}

		temp = temp->next;
	}
	deleteList(&displayed);
}

void deleteSmallest(List* l)
{
	if (l->sz == 0) {
		return; // do nothing, list is empty
	}

	// we can find the index of the smallest element and pass l and the index to remove()
	Node* curr = l->first->next;
	int smallest = l->first->data;

	while (curr) {
		if (curr->data < smallest) {
			smallest = curr->data;
		}

		curr = curr->next;
	}

	remove(l, indexOf(l, smallest));
}

void deleteDuplicates(List* l)
{
	Node* curr = l->first;
	while (curr) {
		while (frequency(l, curr->data) > 1) {
			remove(l, lastIndexOf(l, curr->data));
		}
		curr = curr->next;
	}
}

void deleteNodes(List* l)
{
	// we need to delete on every node
	Node* temp = l->first;
	while (temp) {
		Node* n = temp;
		temp = temp->next;
		delete n;
	}
}

void deleteList(List** l)
{
	deleteNodes(*l);
	delete* l;
	*l = NULL;
}

void reverseDisplay(List* l)
{

	if (l->first == NULL && l->last == NULL) {
		// list is empty
		return; // do nothing
	}
	else if (l->first == l->last) {
		// list contains only 1 element, display it and exit
		cout << l->first->data << endl;
		return;
	}
	else {
		// list contains multiple elements, we need to display them all in reverse order
		Node* curr;
		Node* stop = NULL;
		while (stop != l->first) {
			curr = l->first;
			while (curr->next != stop) {
				curr = curr->next;
			}
			cout << curr->data << " ";
			stop = curr;
		}

		cout << endl;
	}
}

void printMiddle(List* l)
{
	Node* curr = l->first;
	for (int i = 1; i <= l->sz / 2; i++) {
		curr = curr->next;
	}

	cout << "Middle is: " << curr->data << endl;
}

List* pairList(List* l1, List* l2)
{
	Node* temp1 = l1->first;
	Node* temp2 = l2->first;
	List* pair = newList();

	while (temp1 || temp2) {
		if (temp1 != NULL) {
			insertAtEnd(pair, temp1->data);
			temp1 = temp1->next;
		}
		
		if (temp2 != NULL) {
			insertAtEnd(pair, temp2->data);
			temp2 = temp2->next;
		}
	}

	return pair;
}

// this function swaps first and last nodes of the linked list
// note that this isn't checking for size of the list so calling it on empty list
// or a list with only 1 node might result in unexpected behavior
// always perform some checks before calling this
void swapFirstAndLastNode(List* l)
{
	Node* sndLast = previousNode(l, l->last);
	l->last->next = l->first->next; // step 1
	sndLast->next = l->first; // step 2
	l->first->next = NULL; // step 3
	// step 4 is simply changing the pointers
	Node* temp = l->first;
	l->first = l->last;
	l->last = temp;
}

void swapFirstWithKNode(List* l, int k)
{
	Node* n = getIndexBasedNode(l, k);

	if (k == 1) {
		// swap first and second node
		Node* snd = l->first->next;
		l->first->next = snd->next; // step 1
		snd->next = l->first; // step 2
		l->first = snd; // step 3
	}
	else {
		// otherwise apply this logic to swap first node with some arbitrary node
		Node* predeccessorOfN = previousNode(l, n);
		Node* temp = n->next;
		n->next = l->first->next; // step 1
		predeccessorOfN->next = l->first; // step 2
		l->first->next = temp; // step 3
		l->first = n;
	}
}

void swapLastWithKNode(List* l, int k)
{
	Node* n = getIndexBasedNode(l, k);
	Node* predeccessorOfN = previousNode(l, n);
	Node* temp = n->next;
	Node* sndLast = previousNode(l, l->last);

	if (k == l->sz - 2) {
		// swap last and second last node
		Node* predeccessorOfSndLast = previousNode(l, sndLast);
		predeccessorOfSndLast->next = l->last;
		l->last->next = sndLast;
		sndLast->next = NULL;
		l->last = sndLast;
	}
	else {
		// otherwise apply this logic to swap last node with some arbitrary node
		predeccessorOfN->next = l->last;
		l->last->next = temp;
		sndLast->next = n;
		n->next = NULL;
		l->last = n;
	}

}

void swapNonConsecutivePAndK(List* l, int p, int k)
{
	Node* n1 = getIndexBasedNode(l, p);
	Node* n2 = getIndexBasedNode(l, k);
	Node* temp1 = n1->next;
	Node* temp2 = n2->next;
	Node* prev1 = previousNode(l, n1);
	Node* prev2 = previousNode(l, n2);

	// These asserts were added for debugging purposes but I've left them inside
	// These should never be false unless some very specific edge case occurs which probably shouldn't
	// since we are calling this function after doing some checks
	// NOTE: IF THESE ASSERT ARE FAIL THERE IS SOMETHING SERIOUSLY WRONG!!!
	assert(n1 == prev1->next && "n1 == prev1->next");
	assert(n2 == prev2->next && "n2 == prev2->next");
	assert(temp1 == n1->next && "temp1 == n1->next");
	assert(temp2 == n2->next && "temp2 == n2->next");

	prev1->next = n2; // step 1
	n2->next = temp1; // step 2
	prev2->next = n1; // step 3
	n1->next = temp2; // step 4
}

void swapConsecutivePAndK(List* l, int p, int k)
{
	Node* n = getIndexBasedNode(l, p);
	Node* prev = previousNode(l, n);
	Node* temp = n->next;
	prev->next = temp;
	n->next = temp->next;
	temp->next = n;
}

void swapNodes(List* l, int p, int k)
{
	if (l->sz == 0 || l->sz == 1) {
		return; // do nothing, we can't swap on empty list or a list with only 1 node
	}
	else if (p == k) {
		return; // do nothing when both indexes are same also
	}

	if (p == 0 && k == l->sz - 1 ||  p == l->sz - 1 && k == 0) {
		// we want to swap first and last node
		swapFirstAndLastNode(l);
	}
	else if (p == 0 && k != l->sz - 1 && k < l->sz - 1) {
		// k < l->sz - 1 because we don't want an incorrect index
		// this is assuming that p is the index on the left and k is the index on the right
		// we want to swap first node with some arbitrary node
		swapFirstWithKNode(l, k);
	}
	else if (p != 0 && p > 0 && k == l->sz - 1) { // 
		// we p > 0 because we don't want an incorrect index
		// this is assuming that p is the index on the left and k is the index on the right
		// we want to swap last node with some arbitrary node
		swapLastWithKNode(l, p);
	}
	else if (p != 0 && p > 0 && k != l->sz - 1 && k < l->sz - 1 && (abs(p - k) != 1)) {
		// we want to swap some arbitrary nodes and they AREN'T consecutive
		// this is assuming that p is the index on the left and k is the index on the right
		swapNonConsecutivePAndK(l, p, k);
	}
	else if (p != 0 && p > 0 && k != l->sz - 1 && k < l->sz - 1 && (abs(p - k) == 1)) {
		// we want to swap some arbitrary nodes and they ARE consecutive
		// this is assuming that p is the index on the left and k is the index on the right
		swapConsecutivePAndK(l, p, k);
	}
	else {
		cerr << "Error: Invalid indexes passed to swapNodes(List* l, int p, int k): Quitting" << endl;
		std::exit(1);
	}

}

void swapKthNodes(List* l, int k)
{
	swapNodes(l, k - 1, l->sz - k);
}

void addListToSelf(List* l)
{
	List* duplicateList = duplicate(l);
	l->last->next = duplicateList->first;
}

void swapAllNodes(List* l)
{
	for (int i = 0; i < l->sz / 2; i++) {
		swapNodes(l, i, l->sz - 1 - i);
	}
}

void reverseInGroupedSize(List* l, int k)
{
	// how many times to run loop
	int count = l->sz / k;
	if (l->sz % k != 0) {
		count++;
	}

	int i = 0;
	int j = k - 1;
	for (; count > 0; count--) {
		if (count == 1) {
			// last iteration
			// we might now exactly contain k grouped elements
			// such as in case of 1 2 3 4 5 6 7 8 12 7, with k = 4
			j = l->sz - 1;
		}
		
		int tempI = i;
		int tempJ = j;
		while (i < j) {
			swapNodes(l, i, j);
			i++;
			j--;
		}
		i = tempI + k;
		j = tempJ + k;

	}

}

void pairWiseSwapping(List* l)
{
	reverseInGroupedSize(l, 2);
}

int main()
{
	List* l = newList();
	insertAtEnd(l, 20);
	insertAtEnd(l, 18);
	insertAtEnd(l, 15);
	insertAtEnd(l, 10);
	insertAtEnd(l, 8);
	insertAtEnd(l, 6);
	insertAtEnd(l, 5);
	insertAtEnd(l, 3);
	insertAtEnd(l, 7);

	pairWiseSwapping(l);
	display(l);

	deleteList(&l);
}
