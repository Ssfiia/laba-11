#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <Windows.h>
#include "Header.h"

Stack::Stack() : top_(nullptr) {}

// конструктор копирования
Stack::Stack(const Stack& other) : top_(nullptr) {
    if (other.top_ == nullptr) return;
    Stack temp;
    TNode* curr = other.top_;
    while (curr) {
        temp.Push(curr->data);
        curr = curr->next;
    }
    while (!temp.IsEmpty()) {
        Push(temp.Pop());
    }
}

Stack::~Stack() {
    while (top_) {
        TNode* temp = top_;
        top_ = top_->next;
        delete temp;
    }
}

//добавление элемента
void Stack::Push(int value) {
    TNode* new_node = new TNode{ value, top_ };
    top_ = new_node;
}
//удаление элемента с вершины и вернуть его значение
int Stack::Pop() {
    if (IsEmpty()) {
        std::cerr << "Ошибка: стек пуст.\n";
        return -1;
    }
    TNode* temp = top_;
    int value = temp->data;
    top_ = top_->next;
    delete temp;
    return value;
}

TNode* Stack::PopNode() {
    if (IsEmpty()) return nullptr;
    TNode* node = top_;
    top_ = top_->next;
    node->next = nullptr;
    return node;
}
//узел становится новой вершиной
void Stack::PushNode(TNode* node) {
    if (node == nullptr) return;
    node->next = top_;
    top_ = node;
}

bool Stack::IsEmpty() const {
    return top_ == nullptr;
}

void Stack::Print() const {
    TNode* current = top_;
    while (current) {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

bool Stack::Containus(int value) const {
    for (TNode* curr = top_; curr != nullptr; curr = curr->next) {
        if (curr->data == value) {
            return true;
        }
    }
    return false;
}

int Stack::TopValue() const {
    if (IsEmpty()) {
        std::cerr << "Ошибка: стек пуст.\n";
        return -1;
    }
    return top_->data;
}

Queue::Queue() : head_(nullptr), tail_(nullptr) {}

// Конструктор копирования 
Queue::Queue(const Queue& other) : head_(nullptr), tail_(nullptr) {
    TNode* curr = other.head_;
    while (curr) {
        Push(curr->data);
        curr = curr->next;
    }
}

Queue::~Queue() {
    while (head_) {
        TNode* temp = head_;
        head_ = head_->next;
        delete temp;
    }
    tail_ = nullptr;
}
//добавить в конец
void Queue::Push(int value) {
    TNode* new_node = new TNode{ value, nullptr };
    if (IsEmpty()) {
        head_ = tail_ = new_node;
    }
    else {
        tail_->next = new_node;
        tail_ = new_node;
    }
}
//удалить с начала
int Queue::Pop() {
    if (IsEmpty()) {
        std::cerr << "Ошибка: очередь пуста.\n";
        return -1;
    }
    TNode* temp = head_;
    int value = temp->data;
    head_ = head_->next;
    if (head_ == nullptr) tail_ = nullptr;
    delete temp;
    return value;
}

bool Queue::IsEmpty() const {
    return head_ == nullptr;
}

void Queue::Print() const {
    TNode* current = head_;
    while (current) {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

bool Queue::Containus(int value) const {
    for (TNode* curr = head_; curr != nullptr; curr = curr->next) {
        if (curr->data == value) {
            return true;
        }
    }
    return false;
}

List::List() : head_(nullptr) {}

// Конструктор копирования
List::List(const List& other) : head_(nullptr) {
    TNode* curr = other.head_;
    while (curr) {
        AddToEnd(curr->data);
        curr = curr->next;
    }
}

List::~List() {
    while (head_) {
        TNode* temp = head_;
        head_ = head_->next;
        delete temp;
    }
}

void List::AddToEnd(int value) {
    TNode* new_node = new TNode{ value, nullptr };
    if (IsEmpty()) {
        head_ = new_node;
    }
    else {
        TNode* curr = head_;
        while (curr->next) curr = curr->next;
        curr->next = new_node;
    }
}

void List::Print() const {
    TNode* curr = head_;
    while (curr) {
        std::cout << curr->data << " ";
        curr = curr->next;
    }
    std::cout << std::endl;
}

bool List::Containus(int value) const {
    for (TNode* curr = head_; curr != nullptr; curr = curr->next) {
        if (curr->data == value) {
            return true;
        }
    }
    return false;
}

bool List::IsEmpty() const {
    return head_ == nullptr;
}

Stack CreateStackFromConsole() {
    int n;
    std::cout << "Введите количество элементов: ";
    std::cin >> n;
    if (n <= 0) {
        std::cerr << "Количество элементов должно быть положительным.\n";
        return Stack();
    }
    std::vector<int> values(n);
    std::cout << "Введите " << n << " целых чисел: ";
    for (int i = 0; i < n; ++i) {
        std::cin >> values[i];
    }
    Stack s;
    for (int i = n - 1; i >= 0; --i) {
        s.Push(values[i]);  // первый введённый станет вершиной
    }
    return s;
}

Stack CreateStackFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Ошибка открытия файла: " << filename << std::endl;
        return Stack();
    }
    int n;
    file >> n;
    if (n <= 0) {
        std::cerr << "Неверное количество элементов в файле.\n";
        return Stack();
    }
    std::vector<int> values(n);
    for (int i = 0; i < n; ++i) {
        file >> values[i];
    }
    file.close();
    Stack s;
    for (int i = n - 1; i >= 0; --i) {
        s.Push(values[i]);
    }
    return s;
}

Stack CreateStackFromRandom() {
    static bool seeded = false;
    if (!seeded) {
        std::srand(std::time(nullptr));
        seeded = true;
    }
    int n;
    std::cout << "Введите количество случайных элементов: ";
    std::cin >> n;
    if (n <= 0) {
        std::cerr << "Количество элементов должно быть положительным.\n";
        return Stack();
    }
    Stack s;
    for (int i = 0; i < n; ++i) {
        s.Push(std::rand() % 100);
    }
    return s;
}

Queue CreateQueueFromConsole() {
    int n;
    std::cout << "Введите количество элементов: ";
    std::cin >> n;
    if (n <= 0) {
        std::cerr << "Количество элементов должно быть положительным.\n";
        return Queue();
    }
    std::vector<int> values(n);
    std::cout << "Введите " << n << " целых чисел: ";
    for (int i = 0; i < n; ++i) {
        std::cin >> values[i];
    }
    Queue q;
    for (int i = 0; i < n; ++i) {
        q.Push(values[i]);  // первый введённый станет головой
    }
    return q;
}

Queue CreateQueueFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Ошибка открытия файла: " << filename << std::endl;
        return Queue();
    }
    int n;
    file >> n;
    if (n <= 0) {
        std::cerr << "Неверное количество элементов в файле.\n";
        return Queue();
    }
    std::vector<int> values(n);
    for (int i = 0; i < n; ++i) {
        file >> values[i];
    }
    file.close();
    Queue q;
    for (int i = 0; i < n; ++i) {
        q.Push(values[i]);
    }
    return q;
}

Queue CreateQueueFromRandom() {
    static bool seeded = false;
    if (!seeded) {
        std::srand(std::time(nullptr));
        seeded = true;
    }
    int n;
    std::cout << "Введите количество случайных элементов: ";
    std::cin >> n;
    if (n <= 0) {
        std::cerr << "Количество элементов должно быть положительным.\n";
        return Queue();
    }
    Queue q;
    for (int i = 0; i < n; ++i) {
        q.Push(std::rand() % 100);
    }
    return q;
}


List CreateListFromConsole() {
    int n;
    std::cout << "Введите количество элементов: ";
    std::cin >> n;
    if (n <= 0) {
        std::cerr << "Количество элементов должно быть положительным.\n";
        return List();
    }
    std::vector<int> values(n);
    std::cout << "Введите " << n << " целых чисел: ";
    for (int i = 0; i < n; ++i) {
        std::cin >> values[i];
    }
    List lst;
    for (int i = 0; i < n; ++i) {
        lst.AddToEnd(values[i]);  // сохраняем порядок ввода
    }
    return lst;
}

List CreateListFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Ошибка открытия файла: " << filename << std::endl;
        return List();
    }
    int n;
    file >> n;
    if (n <= 0) {
        std::cerr << "Неверное количество элементов в файле.\n";
        return List();
    }
    std::vector<int> values(n);
    for (int i = 0; i < n; ++i) {
        file >> values[i];
    }
    file.close();
    List lst;
    for (int i = 0; i < n; ++i) {
        lst.AddToEnd(values[i]);
    }
    return lst;
}

List CreateListFromRandom() {
    static bool seeded = false;
    if (!seeded) {
        std::srand(std::time(nullptr));
        seeded = true;
    }
    int n;
    std::cout << "Введите количество случайных элементов: ";
    std::cin >> n;
    if (n <= 0) {
        std::cerr << "Количество элементов должно быть положительным.\n";
        return List();
    }
    List lst;
    for (int i = 0; i < n; ++i) {
        lst.AddToEnd(std::rand() % 100);
    }
    return lst;
}

List CreateOrderedListFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Ошибка открытия файла: " << filename << std::endl;
        return List();
    }
    int n;
    file >> n;
    if (n <= 0) {
        std::cerr << "Неверное количество элементов в файле.\n";
        return List();
    }
    List lst;
    int value;
    for (int i = 0; i < n; ++i) {
        if (!(file >> value)) {
            std::cerr << "Ошибка чтения элемента " << i + 1 << std::endl;
            return List();  // возвращаем пустой список
        }
        lst.SortedInsert(value);
    }
    file.close();
    return lst;
}

void List::SortedInsert(int value) {
    TNode* new_node = new TNode{ value, nullptr };
    if (IsEmpty() || value > head_->data) {
        new_node->next = head_;
        head_ = new_node;
        return;
    }
    TNode* curr = head_;
    while (curr->next && curr->next->data >= value) {
        curr = curr->next;
    }
    new_node->next = curr->next;
    curr->next = new_node;
}

TNode* List::GetNodeAt(int index) const {
    if (index < 1) return nullptr;
    TNode* curr = head_;
    for (int i = 1; i < index && curr; ++i) {
        curr = curr->next;
    }
    return curr;
}

void List::InsertAfter(int value) {
    TNode* curr = head_;
    int count = 1;
    while (curr) {
        if (count % 4 == 0) {
            TNode* next_orig = curr->next;
            TNode* new_node = new TNode{ value, next_orig };
            curr->next = new_node;
            curr = next_orig;
        }
        else {
            curr = curr->next;
        }
        ++count;
    }
}