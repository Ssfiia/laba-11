#include <string>

struct TNode {
	int data;
	TNode* next;
};

class Stack {
private:
	TNode* top_;

public:
	Stack();
	Stack(const Stack& other);
	~Stack();

	void Push(int value);
	int Pop();
	TNode* PopNode();
	void PushNode(TNode* node);
	bool IsEmpty() const;
	void Print() const;
	bool Containus(int value) const;
	TNode* GetTop() const { return top_; }
	int TopValue() const;
};

class Queue {
private:
	TNode* head_;
	TNode* tail_;

public:
	Queue();
	Queue(const Queue& other);
	~Queue();

	void Push(int value);                  // добавление в конец
	int Pop();                              // удаление из начала
	bool IsEmpty() const;
	void Print() const;
	bool Containus(int value) const;
	TNode* GetHead() const { return head_; }
	TNode* GetTail() const { return tail_; }
};

class List {
private:
	TNode* head_;

public:
	List();
	List(const List& other);
	~List();

	void AddToEnd(int value);
	void SortedInsert(int value);            // для вставки по убыванию
	TNode* GetNodeAt(int index) const;
	void InsertAfter(int value);
	void Print() const;
	bool Containus(int value) const;
	TNode* GetHead() const { return head_; }
	bool IsEmpty() const;
};

Stack CreateStackFromConsole();
Stack CreateStackFromFile(const std::string& filename);
Stack CreateStackFromRandom();

Queue CreateQueueFromConsole();
Queue CreateQueueFromFile(const std::string& filename);
Queue CreateQueueFromRandom();

List CreateListFromConsole();
List CreateListFromFile(const std::string& filename);
List CreateListFromRandom();
List CreateOrderedListFromFile(const std::string& filename);

void Dynamic6();
void Dynamic28();
void ListWork15();
void ListWork24();
void ListWork62();