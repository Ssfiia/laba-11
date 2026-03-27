#include "Header.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <Windows.h>

//конструктор
DoubleList::DoubleList() : head_(nullptr), tail_(nullptr) {}

//конструктор копировани
DoubleList::DoubleList(const DoubleList& other) : head_(nullptr), tail_(nullptr) {
    TDNode* curr = other.head_;
    while (curr) {
        PushBack(curr->data);
        curr = curr->next;
    }
}

//деконструктор
DoubleList::~DoubleList() {
    Clear();
}

//очищение
void DoubleList::Clear() {
    while (head_) {
        TDNode* temp = head_;
        head_ = head_->next;
        delete temp;
    }
    tail_ = nullptr;
}

//добавть в конец
void DoubleList::PushBack(int value) {
    TDNode* new_node = new TDNode(value, nullptr, tail_);
    if (IsEmpty()) {
        head_ = tail_ = new_node;
    }
    else {
        tail_->next = new_node;
        tail_ = new_node;
    }
}

//добавить в начало
void DoubleList::PushFront(int value) {
    TDNode* new_node = new TDNode(value, head_, nullptr);
    if (IsEmpty()) {
        head_ = tail_ = new_node;
    }
    else {
        head_->prev = new_node;
        head_ = new_node;
    }
}

//вывод в консоль
void DoubleList::Print() const {
    TDNode* curr = head_;
    while (curr) {
        std::cout << curr->data << " ";
        curr = curr->next;
    }
    std::cout << std::endl;
}

//количество элементов
int DoubleList::Count() const {
    int count = 0;
    TDNode* curr = head_;
    while (curr) {
        count++;
        curr = curr->next;
    }
    return count;
}

//поиск элемента
bool DoubleList::Contains(int value) const {
    if (IsEmpty()) return false; 
    for (TDNode* curr = head_; curr != nullptr; curr = curr->next) {
        if (curr->data == value) {
            return true;
        }
    }
    return false;
}

// ListWork65: вывод в файл (последний, первый, предпоследний, второй...)
void DoubleList::PrintFileAfterBefor(const std::string& filename) {
    if (IsEmpty()) {
        std::cerr << "Список пуст. Задача прервана.\n";
        return;
    }
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Ошибка открытия файла: " << filename << std::endl;
        return;
    }
    TDNode* last = tail_;
    TDNode* left = head_;
    TDNode* right = tail_;

    std::cout << "Результат: ";
    bool first = true;
    while (left != right && left->prev != right) {
        if (!first) {
            file << " ";
            std::cout << " ";
        }
        file << right->data;
        std::cout << right->data;
        first = false;
        file << " " << left->data;
        std::cout << " " << left->data;
        left = left->next;
        right = right->prev;
    }
    if (left == right) {
        if (!first) {
            file << " ";
            std::cout << " ";
        }
        file << left->data;
        std::cout << left->data;
    }
    file.close();
    std::cout << std::endl;
    std::cout << "Результат записан в файл " << filename << std::endl;
    Clear();
}

//конструктор
CircularDoubleList::CircularDoubleList(const DoubleList& other) : DoubleList(other) {
    MakeCircular();
}

//конструктор копирования
void CircularDoubleList::MakeCircular() {
    if (head_ && tail_) {
        tail_->next = head_;
        head_->prev = tail_;
    }
}

//деконструктор
CircularDoubleList::~CircularDoubleList() {
    Clear();
}

//количество элементов
int CircularDoubleList::Count() const {
    if (!head_) return 0;
    int count = 0;
    TDNode* curr = head_;
    do {
        count++;
        curr = curr->next;
    } while (curr != head_);
    return count;
}

//вывод в консоль
void CircularDoubleList::PrintCircular() const {
    if (!head_) {
        std::cout << "Список пуст" << std::endl;
        return;
    }
    TDNode* curr = head_;
    do {
        std::cout << curr->data << " ";
        curr = curr->next;
    } while (curr != head_);
    std::cout << std::endl;
}

//поиск значения
bool CircularDoubleList::Contains(int value) const {
    if (IsEmpty()) return false;
    TDNode* curr = head_;
    do {
        if (curr->data == value) {
            return true;
        }
        curr = curr->next;
    } while (curr != head_);
    return false;
}

// ListWork42: удалить элементы, у которых соседи совпадают, вернуть указатель на последний
void CircularDoubleList::DeleteBecauseOfEquals() {
    if (!head_) {
        std::cout << "Список пуст.\n";
        return;
    }
    if (head_->next == head_) {
        std::cout << "Список содержит только 1 элемент, удаление невозможно.\n";
        return;
    }    std::cout << "\nПроверяем элементы:\n";
    std::vector<int> values;
    TDNode* curr = head_;    do {
        values.push_back(curr->data);
        curr = curr->next;
    } while (curr != head_);
    int n = values.size();
    std::vector<bool> keep(n, true);
    std::vector<int> deletedValues;
    for (int i = 0; i < n; i++) {
        int prevIdx = (i - 1 + n) % n;
        int nextIdx = (i + 1) % n;

        if (values[prevIdx] == values[nextIdx]) {
            keep[i] = false;
            deletedValues.push_back(values[i]);
            std::cout << "Элемент " << values[i] << " будет удален (соседи: "
                << values[prevIdx] << " и " << values[nextIdx] << ")" << std::endl;
        }
    }
    if (deletedValues.empty()) {
        std::cout << "Нет элементов для удаления.\n";
        return;
    }
    std::vector<TDNode*> nodesToDelete;
    curr = head_;
    do {
        nodesToDelete.push_back(curr);
        curr = curr->next;
    } while (curr != head_);
    head_ = nullptr;
    tail_ = nullptr;
    for (int i = 0; i < n; i++) {
        if (!keep[i]) {
            delete nodesToDelete[i];
        }
    }
    for (int i = 0; i < n; i++) {
        if (keep[i]) {
            PushBack(values[i]);
        }
    }
    if (head_) {
        MakeCircular();
    }
    std::cout << "\nУдалено элементов: " << deletedValues.size() << std::endl;
    if (!deletedValues.empty()) {
        std::cout << "Удаленные элементы: ";
        for (size_t i = 0; i < deletedValues.size(); i++) {
            std::cout << deletedValues[i];
            if (i < deletedValues.size() - 1) std::cout << " ";
        }
        std::cout << std::endl;
    }
}

//конструктор списка с барьером
BarrierList::BarrierList() {
    barrier_ = new TDNode(0);
    barrier_->next = barrier_;
    barrier_->prev = barrier_;
    current_ = barrier_;
}

//конструктор копирования
BarrierList::BarrierList(const DoubleList& other) : BarrierList() {
    TDNode* curr = other.GetHead();
    while (curr) {
        InsertLast(curr->data);
        curr = curr->next;
    }
}

//деконструктор
BarrierList::~BarrierList() {
    TDNode* curr = barrier_->next;
    while (curr != barrier_) {
        TDNode* temp = curr;
        curr = curr->next;
        delete temp;
    }
    delete barrier_;
}

//добавить перед барьером
void BarrierList::InsertLast(int value) {
    TDNode* new_node = new TDNode(value, barrier_, barrier_->prev);
    barrier_->prev->next = new_node;
    barrier_->prev = new_node;
    current_ = new_node;
}

//количество
int BarrierList::Count() const {
    int count = 0;
    TDNode* curr = barrier_->next;
    while (curr != barrier_) {
        count++;
        curr = curr->next;
    }
    return count;
}

//вывод в консоль
void BarrierList::Print() const {
    if (barrier_->next == barrier_) {
        std::cout << "Список пуст" << std::endl;
        return;
    }
    TDNode* curr = barrier_->next;
    while (curr != barrier_) {
        std::cout << curr->data << " ";
        curr = curr->next;
    }

    std::cout << std::endl;
}

//поиск значения
bool BarrierList::Contains(int value) const {
    if (barrier_->next == barrier_) return false;
    for (TDNode* curr = barrier_->next; curr != barrier_; curr = curr->next) {
        if (curr->data == value) {
            return true;
        }
    }
    return false;
}

//создаём структуру из списка
TListB BarrierList::GetTListB() const {
    TListB tlb;
    tlb.Barrier = barrier_;
    tlb.Current = current_;
    return tlb;
}

//востанавливаем список из структуры
void BarrierList::FromTListB(const TListB& tlb) {
    barrier_ = tlb.Barrier;
    current_ = tlb.Current;
}

// ListWork48: присвоить нулевые значения элементам с нечетными номерами через TListB
void BarrierList::AssignZero() {
    if (barrier_->next == barrier_) {
        std::cout << "Список пуст.\n";
        std::cout << "Количество элементов: 0\n";
        std::cout << "Адрес текущего элемента (барьерный): " << static_cast<void*>(barrier_) << std::endl;
        return;
    }
    TListB tlb = GetTListB();
    LBToFirst(tlb);
    int totalCount = Count(); 
    int changedCount = 0;
    for (int i = 1; i <= totalCount; i++) {
        if (!IsBarrier(tlb)) {
            if (i % 2 == 1) {
                LBSetData(tlb, 0);
                changedCount++;
            }
        }
        if (i < totalCount) LBToNext(tlb);
    }
    tlb.Current = barrier_;
    FromTListB(tlb);
    std::cout << "Количество элементов в списке: " << totalCount << std::endl;
    std::cout << "Изменено элементов (нечетные номера): " << changedCount << std::endl;
    std::cout << "Новый адрес текущего элемента (барьерный): " << static_cast<void*>(barrier_) << std::endl;
    std::cout << "Список после изменений: ";
    Print();
}

//конструктор
CircularList::CircularList() : head_(nullptr) {}

//конструктор копирования
CircularList::CircularList(const CircularList& other) : head_(nullptr) {
    if (other.IsEmpty()) return;

    TNode* curr = other.head_;
    do {
        PushBack(curr->data);
        curr = curr->next;
    } while (curr != other.head_);
}

//деконструктор
CircularList::~CircularList() {
    Clear();
}

//очищение
void CircularList::Clear() {
    if (IsEmpty()) return;
    TNode* curr = head_;
    TNode* nextNode;
    do {
        nextNode = curr->next;
        delete curr;
        curr = nextNode;
    } while (curr != head_);

    head_ = nullptr;
}

//добавить в конец
void CircularList::PushBack(int value) {
    TNode* new_node = new TNode{ value, nullptr };

    if (IsEmpty()) {
        head_ = new_node;
        new_node->next = head_;
    }
    else {
        TNode* last = head_;
        while (last->next != head_) {
            last = last->next;
        }
        last->next = new_node;
        new_node->next = head_;
    }
}

//поиск значения
bool CircularList::Contains(int value) const {
    if (IsEmpty()) return false;
    TNode* curr = head_;
    do {
        if (curr->data == value) {
            return true;
        }
        curr = curr->next;
    } while (curr != head_);
    return false;
}

// ListWork69: вывод в файл с шагом k и удалением
void CircularList::PrintToFileWithStep(const std::string& filename, int k) {
    if (IsEmpty()) {
        std::cerr << "Список пуст. Задача прервана.\n";
        return;
    }
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Ошибка открытия файла: " << filename << std::endl;
        return;
    }
    TNode* current = head_;
    bool firstElement = true;
    int stepCount = 1;
    while (!IsEmpty()) {
        stepCount++;
        std::cout << current->data << " ";
        if (!firstElement) file << " ";
        file << current->data;
        firstElement = false;
        if (current->next == current) {
            delete current;
            head_ = nullptr;
            break;
        }
        TNode* prev = current;
        while (prev->next != current) {
            prev = prev->next;
        }
        TNode* nextInLine = current->next;
        prev->next = nextInLine;

        if (current == head_) {
            head_ = nextInLine;
        }
        delete current;
        current = nextInLine;
        for (int i = 1; i < k; i++) {
            current = current->next;
        }
    }
    file.close();
    std::cout << std::endl;
    std::cout << "Результат записан в файл " << filename << std::endl;
}

//конструктор
ChildrenCircle::ChildrenCircle() : head_(nullptr), count_(0) {}

//деконструктор
ChildrenCircle::~ChildrenCircle() {
    Clear();
}

//очистка
void ChildrenCircle::Clear() {
    if (!head_) return;

    ChildNode* current = head_;
    ChildNode* nextNode;

    do {
        nextNode = current->next;
        delete current;
        current = nextNode;
    } while (current != head_);

    head_ = nullptr;
    count_ = 0;
}

//поиск значения
bool ChildrenCircle::Contains(const std::string& name) const {
    if (IsEmpty()) return false;
    ChildNode* curr = head_;
    do {
        if (curr->name == name) {
            return true;
        }
        curr = curr->next;
    } while (curr != head_);
    return false;
}

//чтение имён детей в файле
bool ChildrenCircle::LoadChildrenFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Ошибка: Не удалось открыть файл " << filename << std::endl;
        return false;
    }
    Clear();
    std::string name;
    std::vector<std::string> names;
    while (std::getline(file, name)) {
        if (!name.empty()) {
            names.push_back(name);
        }
    }
    file.close();
    if (names.empty()) {
        std::cerr << "Ошибка: Нет имен детей в файле" << std::endl;
        return false;
    }
    for (const auto& childName : names) {
        ChildNode* newNode = new ChildNode(childName);
        if (!head_) {
            head_ = newNode;
            head_->next = head_;
        }
        else {
            ChildNode* last = head_;
            while (last->next != head_) {
                last = last->next;
            }
            last->next = newNode;
            newNode->next = head_;
        }
        count_++;
    }
    std::cout << "Загружено детей: " << count_ << std::endl;
    return true;
}

//загрузка из файла
std::vector<std::string> ChildrenCircle::LoadRhymeFromFile(const std::string& filename) {
    std::vector<std::string> words;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Ошибка: Не удалось открыть файл считалки " << filename << std::endl;
        return words;
    }
    std::string word;
    while (file >> word) {
        words.push_back(word);
    }
    file.close();
    std::cout << "Загружено слов в считалке: " << words.size() << std::endl;
    return words;
}

//ввод считалочки
std::vector<std::string> ChildrenCircle::InputRhymeFromConsole() {
    std::vector<std::string> words;
    std::cout << "Введите слова считалки (введите 'стоп' для завершения):" << std::endl;
    std::string word;
    while (true) {
        std::cout << "Считалка: ";
        std::cin >> word;
        if (word == "стоп" || word == "stop") {
            break;
        }

        words.push_back(word);
    }
    std::cout << "Введено слов в считалке: " << words.size() << std::endl;
    return words;
}

//вывод имён детей в консоль
void ChildrenCircle::Print() const {
    if (!head_) {
        std::cout << "Круг пуст" << std::endl;
        return;
    }
    ChildNode* current = head_;
    std::cout << "Дети в кругу: ";
    do {
        std::cout << current->name;
        current = current->next;
        if (current != head_) std::cout << " -> ";
    } while (current != head_);
    std::cout << " (замкнуто)" << std::endl;
}

//игра
void ChildrenCircle::SolveGame(const std::string& outputFilename) {
    if (!head_ || count_ == 0) {
        std::cerr << "Ошибка: Круг пуст!" << std::endl;
        return;
    }
    std::vector<std::string> rhyme;
    std::cout << "\nВыберите способ ввода считалки:\n";
    std::cout << "1. Из файла\n";
    std::cout << "2. С консоли\n";
    std::cout << "Выбор: ";
    int choice;
    std::cin >> choice;
    if (choice == 1) {
        std::string rhymeFile;
        std::cout << "Введите имя файла со считалкой: ";
        std::cin >> rhymeFile;
        rhyme = LoadRhymeFromFile(rhymeFile);
    }
    else if (choice == 2) {
        rhyme = InputRhymeFromConsole();
    }
    else {
        std::cerr << "Неверный выбор. Задача прервана.\n";
        return;
    }
    if (rhyme.empty()) {
        std::cerr << "Считалочка пуста. Задача прервана.\n";
        return;
    }
    std::cout << "\nСчиталочка (" << rhyme.size() << " слов): ";
    for (const auto& w : rhyme) {
        std::cout << w << " ";
    }
    std::cout << std::endl;
    std::ofstream outFile(outputFilename);
    if (!outFile.is_open()) {
        std::cerr << "Ошибка: Не удалось создать выходной файл " << outputFilename << std::endl;
        return;
    }
    std::cout << "\n Начинаем игру " << std::endl;
    ChildNode* current = head_;
    ChildNode* prev = nullptr;
    prev = head_;
    while (prev->next != head_) {
        prev = prev->next;
    }
    int remaining = count_;
    int rhymeSize = rhyme.size();
    int roundNumber = 1;
    std::vector<std::string> eliminationOrder;
    std::cout << "\nПорядок выбывания детей:\n";
    while (remaining > 0) {
        std::cout << "Раунд " << std::setw(2) << roundNumber++ << ": ";
        for (int i = 0; i < rhymeSize; i++) {
            if (i == rhymeSize - 1) {
                std::cout << std::setw(7) << std::left << current->name << " выбывает!";
                eliminationOrder.push_back(current->name);
                outFile << current->name << std::endl;
                ChildNode* toDelete = current;
                if (current == head_ && remaining == 1) {
                    head_ = nullptr;
                    prev = nullptr;
                    current = nullptr;
                }
                else {
                    prev->next = current->next;
                    if (current == head_) {
                        head_ = current->next;
                    }
                    current = current->next;
                }
                delete toDelete;
                remaining--;
                std::cout << std::endl;
                break;
            }
            else {
                prev = current;
                current = current->next;
            }
        }
    }
    std::cout << "Игра завершена! Все дети выбыли." << std::endl;
    std::cout << "\n Порядок выбывания:\n";
    for (size_t i = 0; i < eliminationOrder.size(); i++) {
        std::cout << i + 1 << ". " << eliminationOrder[i] << std::endl;
    }
    std::cout << "\nРезультат записан в файл: " << outputFilename << std::endl;
    outFile.close();
}

//переход к первому
void LBToFirst(TListB& L) {
    if (L.Barrier && L.Barrier->next != L.Barrier) {
        L.Current = L.Barrier->next;
    }
}

//переход к следующему
void LBToNext(TListB& L) {
    if (L.Current && L.Current->next != L.Barrier) {
        L.Current = L.Current->next;
    }
}

//присвоение данных
void LBSetData(TListB& L, int D) {
    if (L.Current && L.Current != L.Barrier) {
        L.Current->data = D;
    }
}

//проверка барьер ли 
bool IsBarrier(const TListB& L) {
    return L.Current == L.Barrier;
}