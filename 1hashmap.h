#pragma once
#include <iostream>
using namespace std;


class HashMapNode
{
public:
	string key;
	int value;

	HashMapNode* prevAdd;
	HashMapNode* nextAdd;

	HashMapNode(string key, int data) {
		this->key = key;
		this->value = data;
		this->prevAdd = NULL;
		this->nextAdd = NULL;
	};
	~HashMapNode() {
	};

	void display() {
		cout << "Insititution :" << key << ", " << "Count: " << value << endl;
	}

private:

};

class HashMapDoubleLinkedList
{
public:
	HashMapNode* head;
	HashMapNode* tail;

	int getSize() {
		return size;
	}

	HashMapDoubleLinkedList() {
		size = 0;
		head = NULL;
		tail = NULL;
	};

	void insertFront(HashMapNode* newNode) { // O(1)
		if (head == NULL)
		{
			head = tail = newNode;
		}
		else
		{
			newNode->nextAdd = head;
			head->prevAdd = newNode;
			head = newNode;
		}

		size++;
	}

	void insertEnd(HashMapNode* newNode) { // O(1)
		if (head == NULL)
		{
			head = tail = newNode;
		}
		else
		{
			tail->nextAdd = newNode;
			newNode->prevAdd = tail;
			tail = newNode;
		}

		size++;
	}
	HashMapNode* getHead() {
        return head;
    }
	void displayAll() { // O(n)
		HashMapNode* current = head;

		while (current != NULL)
		{
			current->display();
			cout << endl;
			current = current->nextAdd;
		}

		cout << "List is ended here!" << endl;
	}
private:
	int size;

};


class HashMap
{
public:
    HashMapNode* linearSearchByKey(HashMapNode* head, string targetkey) {
    HashMapNode* current = head;
    
    while (current != nullptr) {
        if (current->key == targetkey) {
            return current; 
        }
        current = current->nextAdd;
    }
    
    return nullptr; 
}

	HashMapDoubleLinkedList HashMapdll;
	HashMap() {
	}
	
	void setValue(string key, int value) {
		
        HashMapNode* node = this->linearSearchByKey(HashMapdll.head,key);

		if (node == NULL) {
			HashMapNode* newNode = new HashMapNode(key, value);
			this->HashMapdll.insertEnd(newNode);
		}
		else
		{
			node->value = value;
		}
		return;
	}
	int getValue(string key) {
		
        HashMapNode* node = this->linearSearchByKey(HashMapdll.head,key);

		if (node == NULL)
		{
			return -1;
		}
		else
		{
			return node->value;
		}

		return -1;
	}
	void display() {
		HashMapNode* head = HashMapdll.getHead(); // Retrieve the head pointer
    HashMapNode* current = head;
    vector<HashMapNode*> nodes;

    while (current != nullptr) {
        nodes.push_back(current);
        current = current->nextAdd;
    }

    // Sort nodes based on the value attribute in descending order
    sort(nodes.begin(), nodes.end(), [](const HashMapNode* a, const HashMapNode* b) {
        return a->value > b->value;
    });

    for (const auto& node : nodes) {
        node->display();
        cout << endl;
    }

    cout << "List is ended here!" << endl;
	}
	
	bool hasKey(string key) {
		
        HashMapNode* node = this->linearSearchByKey(HashMapdll.head,key);
		
        if (node == NULL)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
};