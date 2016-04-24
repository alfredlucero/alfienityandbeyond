#ifndef INTLIST_INCLUDED
#define INTLIST_INCLUDED

struct Node {
	int m_data;
	Node* m_next;
};

class IntList {
public:
	IntList();
	IntList(int value);
	~IntList();
	void insertInt(int value);
	void deleteInt(int value);
	void printIntList() const;
	int getSumIntList() const;
private:
	Node* m_head;
	int m_total;
};

#endif // INTLIST_INCLUDED