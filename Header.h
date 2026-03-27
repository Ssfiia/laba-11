#include <string>
#include <vector>
#include <iostream>

class TNode {
public:
    int data;
    TNode* next;
};

// Двусвязный список
class TDNode {
public:
    int data;
    TDNode* next;
    TDNode* prev;
    TDNode(int val = 0, TDNode* n = nullptr, TDNode* p = nullptr) : data(val), next(n), prev(p) {}
};

// Структура TListB для работы со списком с барьером
class TListB {
public:
    TDNode* Barrier;
    TDNode* Current;

    TListB() : Barrier(nullptr), Current(nullptr) {}
};

// Класс двусвязного списка
class DoubleList {
protected:
    TDNode* head_;
    TDNode* tail_;

public:
    DoubleList();
    DoubleList(const DoubleList& other);
    ~DoubleList();

    void PushBack(int value);
    void PushFront(int value);
    void Print() const;
    bool IsEmpty() const { return head_ == nullptr; }
    bool Contains(int value) const;
    TDNode* GetHead() const { return head_; }
    TDNode* GetTail() const { return tail_; }

    void PrintFileAfterBefor(const std::string& filename);

    int Count() const;
    void Clear();
};

// Класс циклического двусвязного списка
class CircularDoubleList : public DoubleList {
public:
    CircularDoubleList() : DoubleList() {}
    CircularDoubleList(const DoubleList& other);
    ~CircularDoubleList();

    int Count() const;
    void MakeCircular();
    void PrintCircular() const;
    bool Contains(int value) const;
    void DeleteBecauseOfEquals();
};

// Класс для списка с барьерным элементом
class BarrierList {
private:
    TDNode* barrier_;
    TDNode* current_;

public:
    BarrierList();
    BarrierList(const DoubleList& other);
    ~BarrierList();

    void InsertLast(int value);

    TDNode* GetBarrier() const { return barrier_; }
    TDNode* GetCurrent() const { return current_; }
    void SetCurrent(TDNode* curr) { current_ = curr; }

    void Print() const;
    int Count() const;
    bool Contains(int value) const;
    TListB GetTListB() const;
    void FromTListB(const TListB& tlb);

    void AssignZero();
};

// Класс для циклического односвязного списка
class CircularList {
private:
    TNode* head_;

public:
    CircularList();
    CircularList(const CircularList& other);
    ~CircularList();

    void PushBack(int value);
    bool Contains(int value) const;
    bool IsEmpty() const { return head_ == nullptr; }
    TNode* GetHead() const { return head_; }

    // ListWork69 - вывод в файл с шагом k и удалением
    void PrintToFileWithStep(const std::string& filename, int k);

private:
    void Clear();
};


class ChildNode {
public:
    std::string name;
    ChildNode* next;
    ChildNode(const std::string& n) : name(n), next(nullptr) {}
};

// Класс для задачи "Считалка"
class ChildrenCircle {
private:
    ChildNode* head_;
    int count_;

public:
    ChildrenCircle();
    ~ChildrenCircle();

    bool LoadChildrenFromFile(const std::string& filename);
    std::vector<std::string> LoadRhymeFromFile(const std::string& filename);
    std::vector<std::string> InputRhymeFromConsole();
    void SolveGame(const std::string& outputFilename);
    void Print() const;
    bool IsEmpty() const { return head_ == nullptr; }
    int Count() const { return count_; }
    bool Contains(const std::string& name) const;

private:
    void Clear();
};

// Процедуры для TListB (ListWork48)
void LBToFirst(TListB& L);
void LBToNext(TListB& L);
void LBSetData(TListB& L, int D);
bool IsBarrier(const TListB& L);

// Функции выбора для новых типов
DoubleList ChooseDoubleList(const std::string& prompt);
CircularList ChooseCircularList(const std::string& prompt);
BarrierList ChooseBarrierList(const std::string& prompt);

// Новые задачи
void ListWork42();  // Циклический двусвязный: удалить где соседи равны
void ListWork48();  // Список с барьером: присвоить 0 нечетным элементам
void ListWork65();  // Двусвязный: вывод в файл (последний, первый...)
void ListWork69();  // Циклический список с шагом k
void ChildrenGame(); // Задача "Считалка" с именами детей