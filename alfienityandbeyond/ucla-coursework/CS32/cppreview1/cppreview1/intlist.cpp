#include "intlist.h";
#include <iostream>;

using namespace std;

IntList::IntList() {
	m_head = nullptr;
	m_total = 0;
}

IntList::IntList(int value) {
	Node * first = new Node;
	first->m_data = value;
	first->m_next = nullptr;
	m_head = first;
}

IntList::~IntList() {
	Node * temp = m_head;
	while (temp->m_next != nullptr) {
		Node * next = temp->m_next;
		delete temp;
		temp = next;
	}
}

void IntList::insertInt(int value) {
	// Add first new element in the list
	if (m_head == nullptr) {
		m_head = new Node;
		m_head->m_data = value;
		m_head->m_next = nullptr;
		m_total += value;

		return;
	} 
	
	// Check for insertion to front of the list
	if (m_head->m_next == nullptr) {
		// If the value is < the front element, insert before it 
		if (value < m_head->m_data) {
			Node * toInsert = new Node;
			toInsert->m_data = value;
			toInsert->m_next = m_head;
			m_head = toInsert;
			m_total += value;
		}

		return;
	}

	// Find position to insert middle/last element
	Node * iter = m_head;
	while (iter->m_next != nullptr) {
		if (value >= iter->m_data && value <= iter->m_next->m_data) {
			break;
		}
		iter = iter->m_next;
	}

	// Insert the interior node
	Node * toInsert = new Node; 
	toInsert->m_data = value;
	toInsert->m_next = iter->m_next;
	iter->m_next = toInsert;
	m_total += value;
}


void IntList::deleteInt(int value) {
	// Empty list
	if (m_head == nullptr) {
		return;
	}
	
	if (m_head->m_data == value) { // Check if the value is in the first node to remove
		Node * toDelete = m_head;
		m_head = m_head->m_next;
		delete toDelete;
		m_total -= value;

		return;
	} else { // Delete interior/last node if value exists
		Node * iter = m_head;
		while (iter->m_next != nullptr) {
			if (iter->m_next->m_data == value)
				break;

			iter = iter->m_next;
		}

		// No matches if nullptr so don't delete anything
		if (iter->m_next == nullptr)
			return;

		Node * toDelete = iter->m_next;
		iter->m_next = toDelete->m_next;
		delete toDelete;
		m_total -= value;
	}
}

void IntList::printIntList() const {
	for (Node * iter = m_head; iter != nullptr; iter = iter->m_next)
		cout << iter->m_data << endl;
}

int IntList::getSumIntList() const {
	return m_total;
}