#include <iostream>
#include <string>
#include <vector>

using namespace std;

template<class ItemType>
class Node {
private:
	ItemType item;
	Node<ItemType>* prev;
	Node<ItemType>* next;
public:
	Node();
	Node(const ItemType anItem);
	Node(const ItemType anItem, Node<ItemType>* prevNodePtr, Node<ItemType>* nextNodePtr);
	void setItem(const ItemType anItem);
	void setPrev(Node<ItemType>* prevNodePtr);
	void setNext(Node<ItemType>* nextNodePtr);
	ItemType getItem() const;
	Node<ItemType>* getPrev() const;
	Node<ItemType>* getNext() const;
};



template<class ItemType>
Node<ItemType>::Node() : prev(nullptr), next(nullptr) {

}



template<class ItemType>
Node<ItemType>::Node(const ItemType anItem) : item(anItem), prev(nullptr), next(nullptr) {

}



template<class ItemType>
Node<ItemType>::Node(const ItemType anItem, Node<ItemType>* prevNodePtr, Node<ItemType>* nextNodePtr) :
	item(anItem), prev(prevNodePtr), next(nextNodePtr) {
}



template<class ItemType>
void Node<ItemType>::setItem(const ItemType anItem) {
	item = anItem;
}



template<class ItemType>
void Node<ItemType>::setPrev(Node<ItemType>* prevNodePtr) {
	prev = prevNodePtr;
}



template<class ItemType>
void Node<ItemType>::setNext(Node<ItemType>* nextNodePtr) {
	next = nextNodePtr;
}



template<class ItemType>
ItemType Node<ItemType>::getItem() const {
	return item;
}



template<class ItemType>
Node<ItemType>* Node<ItemType>::getPrev() const {
	return prev;
}



template<class ItemType>
Node<ItemType>* Node<ItemType>::getNext() const {
	return next;
}





template<class ItemType>
class LinkedBag {
private:
	Node<ItemType>* headPtr;
	int itemCount;
	Node<ItemType>* getPointerTo(const ItemType& target) const;
public:
	LinkedBag();
	LinkedBag(const LinkedBag<ItemType>& aBag);
	virtual ~LinkedBag();
	int getCurrentSize() const;
	bool isEmpty() const;
	bool add(const ItemType& newEntry);
	bool remove(const ItemType& anEntry);
	void clear();
	bool contains(const ItemType& anEntry) const;
	int getFrequencyOf(const ItemType& anEntry) const;
	vector<ItemType> toVector() const;
	Node<ItemType>* getHead() const;
};



template<class ItemType>
Node<ItemType>* LinkedBag<ItemType>::getPointerTo(const ItemType& target) const {
	bool found = false;
	Node<ItemType>* curPtr = headPtr;
	while (!found && (curPtr != nullptr)) {
		if (target == curPtr->getItem())
			found = true;
		else
			curPtr = curPtr->getNext();
	}
	return curPtr;
}



template<class ItemType>
LinkedBag<ItemType>::LinkedBag() : headPtr(nullptr), itemCount(0) {

}



template<class ItemType>
LinkedBag<ItemType>::LinkedBag(const LinkedBag<ItemType>& aBag) {

	itemCount = aBag.itemCount;
	Node<ItemType>* origChainPtr = aBag.headPtr;

	if (origChainPtr == nullptr)
		headPtr = nullptr;
	else {
		headPtr = new Node<ItemType>();
		headPtr->setItem(origChainPtr->getItem());

		Node<ItemType>* newChainPtr = headPtr;

		origChainPtr = origChainPtr->getNext();
		while (origChainPtr != nullptr) {

			Node<ItemType>* newNodePtr = new Node<ItemType>(origChainPtr->getItem());
			newChainPtr->setPrev(origChainPtr);
			newChainPtr->setNext(newNodePtr);
			newChainPtr = newChainPtr->getNext();

			origChainPtr = origChainPtr->getNext();
		}
		newChainPtr->setNext(nullptr);
	}
}



template<class ItemType>
LinkedBag<ItemType>::~LinkedBag() {
	clear();
}



template<class ItemType>
bool LinkedBag<ItemType>::add(const ItemType& newEntry) {
	Node<ItemType>* newNodePtr = new Node<ItemType>();
	newNodePtr->setItem(newEntry);
	if (headPtr != nullptr) {
		newNodePtr->setNext(headPtr);
		headPtr->setPrev(newNodePtr);
	}
	headPtr = newNodePtr;
	itemCount++;

	return true;
}



template<class ItemType>
bool LinkedBag<ItemType>::remove(const ItemType& anEntry) {
	Node<ItemType>* entryNodePtr = getPointerTo(anEntry);
	bool canRemoveItem = !isEmpty() && (entryNodePtr != nullptr);
	if (canRemoveItem) {
		entryNodePtr->setItem(headPtr->getItem());

		Node<ItemType>* nodeToDeletePtr = headPtr;
		headPtr = headPtr->getNext();

		headPtr->setPrev(nullptr);
		nodeToDeletePtr->setNext(nullptr);
		delete nodeToDeletePtr;
		nodeToDeletePtr = nullptr;

		itemCount--;
	}
	return canRemoveItem;
}



template<class ItemType>
void LinkedBag<ItemType>::clear() {
	Node<ItemType>* nodeToDeletePtr = headPtr;

	while (headPtr != nullptr) {
		headPtr = headPtr->getNext();
		if(headPtr != nullptr)
			headPtr->setPrev(nullptr);
		nodeToDeletePtr->setNext(nullptr);
		delete nodeToDeletePtr;
		nodeToDeletePtr = headPtr;
	}
	itemCount = 0;
}



template<class ItemType>
bool LinkedBag<ItemType>::isEmpty() const {
	return itemCount == 0;
}



template<class ItemType>
int LinkedBag<ItemType>::getCurrentSize() const {
	return itemCount;
}



template<class ItemType>
bool LinkedBag<ItemType>::contains(const ItemType& anEntry) const {
	return (getPointerTo(anEntry) != nullptr);
}



template<class ItemType>
int LinkedBag<ItemType>::getFrequencyOf(const ItemType& anEntry) const {
	int frequency = 0;
	int counter = 0;
	Node<ItemType>* curPtr = headPtr;
	while ((curPtr != nullptr) && (counter < itemCount)) {
		if (anEntry == curPtr->getItem())
			frequency++;
		counter++;
		curPtr = curPtr->getNext();
	}
	return frequency;
}



template<class ItemType>
vector<ItemType> LinkedBag<ItemType>::toVector() const {
	vector<ItemType> bagContents;
	Node<ItemType>* curPtr = headPtr;
	int counter = 0;
	while ((curPtr != nullptr) && (counter < itemCount)) {
		bagContents.push_back(curPtr->getItem());
		curPtr = curPtr->getNext();
		counter++;
	}
	return bagContents;
}





int main()
{
	LinkedBag<string> LinkedList;
	
	LinkedList.add("first");
	
	LinkedList.add("second");
	LinkedList.add("thirds");
	LinkedList.add("first");
	
	cout << "List of words  in LinkedList: " << endl;
	vector<string> listWords = LinkedList.toVector();
	for (int i = 0; i < LinkedList.getCurrentSize(); i++) {
		cout << listWords.at(i) << endl;
	}

	LinkedBag<string> anotherList(LinkedList);
	cout << "\ncopied LinkedList to anotherList" << endl;

	cout << "Frequency of first in LinkedList is: " << LinkedList.getFrequencyOf("first") << endl;
	cout << "Number of Nodes in LinkedList: " << LinkedList.getCurrentSize() << endl;
	cout << "Does LinkedList contain second? 1 for yes, 0 for no: " << LinkedList.contains("second") << endl;

	LinkedList.remove("second");
	cout << "\nremoved second" << endl;
	cout << "Does Linked List contain second? 1 for yes, 0 for no: " << LinkedList.contains("second") << endl;

	cout << "\nIs Linked List empty? 1 for yes, 0 for no: " << LinkedList.isEmpty() << endl;
	LinkedList.clear();
	cout << "LinkedList cleared." << endl;
	cout << "Is Linked List empty? 1 for yes, 0 for no: " << LinkedList.isEmpty() << endl << endl;

	cout << "List of words in anotherList: " << endl;
	listWords = anotherList.toVector();
	for (int i = 0; i < anotherList.getCurrentSize(); i++) {
		cout << listWords.at(i) << endl;
	}

	cout << "\nFrequency of first anotherList is: " << anotherList.getFrequencyOf("first") << endl;
	cout << "Number of Nodes in anotherList is: " << anotherList.getCurrentSize() << endl;
	cout << "Does anotherList contain second? 1 for yes, 0 for no: " << anotherList.contains("second") << endl;
}


