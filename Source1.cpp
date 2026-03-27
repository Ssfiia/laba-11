#include "Header.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <Windows.h>

static Stack ChooseStack(const std::string& pr) {
    std::cout << pr << "\n";
    std::cout << "1. С консоли\n";
    std::cout << "2. Из файла\n";
    std::cout << "3. Рандом\n";
    std::cout << "Ваш выбор: ";
    int ch;
    std::cin >> ch;
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore();
        std::cout << "Ошибка ввода! /n";
    }
    switch (ch) {
    case 1: return CreateStackFromConsole();
    case 2: {
        std::string filename;
        std::cout << "Введите имя файла: ";
        std::cin >> filename;
        return CreateStackFromFile(filename);
    }
    case 3: return CreateStackFromRandom();
    default:
        std::cerr << "Неверный выбор. Возвращён пустой стек.\n";
        return Stack();
    }
}

static Queue ChooseQueue(const std::string& pr) {
    std::cout << pr << "\n";
    std::cout << "1. С консоли\n";
    std::cout << "2. Из файла\n";
    std::cout << "3. Рандом\n";
    std::cout << "Ваш выбор: ";
    int choice;
    std::cin >> choice;
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore();
        std::cout << "Ошибка ввода! /n";
    }

    switch (choice) {
    case 1: return CreateQueueFromConsole();
    case 2: {
        std::string filename;
        std::cout << "Введите имя файла: ";
        std::cin >> filename;
        return CreateQueueFromFile(filename);
    }
    case 3: return CreateQueueFromRandom();
    default:
        std::cerr << "Неверный выбор. Возвращена пустая очередь.\n";
        return Queue();
    }
}

static List ChooseList(const std::string& pr) {
    std::cout << pr << "\n";
    std::cout << "1. С консоли\n";
    std::cout << "2. Из файла\n";
    std::cout << "3. Рандом\n";
    std::cout << "Ваш выбор: ";
    int choice;
    std::cin >> choice;
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore();
        std::cout << "Ошибка ввода! /n";
    }
    switch (choice) {
    case 1: return CreateListFromConsole();
    case 2: {
        std::string filename;
        std::cout << "Введите имя файла: ";
        std::cin >> filename;
        return CreateListFromFile(filename);
    }
    case 3: return CreateListFromRandom();
    default:
        std::cerr << "Неверный выбор. Возвращён пустой список.\n";
        return List();
    }
}

// Извлечь первые 9 элементов стека
void Dynamic6() {
    std::cout << "\nЗадача 1 Dynamic6: Извлечь первые 9 элементов из стека.\n";
    Stack s = ChooseStack("Выберите способ заполнения стека:");
    if (s.IsEmpty()) {
        std::cerr << "Стек пуст. Задача прервана.\n";
        return;
    }
    Stack temp = s;
    int count = 0;
    while (!temp.IsEmpty()) {
        temp.Pop();
        count++;
    }
    if (count < 10) {
        std::cerr << "Ошибка: в стеке менее 10 элементов (всего " << count << "). Задача прервана.\n";
        return;
    }
    std::cout << "Исходный стек: ";
    s.Print();
    std::cout << "Адрес вершины: " << static_cast<void*>(s.GetTop()) << std::endl;
    std::cout << "Значение вершины: " << s.TopValue() << std::endl;
    std::cout << "Извлечённые элементы: ";

    for (int i = 0; i < 9; i++) {
        std::cout << s.Pop() << " ";
    }
    std::cout << std::endl;
    if (!s.IsEmpty()) {
        std::cout << "Новый адрес вершины: " << static_cast<void*>(s.GetTop()) << std::endl;
        std::cout << "Новое значение вершины: " << s.TopValue() << std::endl;
        std::cout << "Оставшийся стек: ";
        s.Print();
    }
    else {
        std::cout << "Новый адрес вершины: nullptr (стек опустел)" << std::endl;
    }
}

// Извлечь первые 5 элементов очереди с проверкой пустоты
void Dynamic28() {
    std::cout << "\nЗадача 2 Dynamic28: Извлечь первые 5 элементов из очереди.\n";

    Queue q = ChooseQueue("Выберите способ заполнения очереди:");
    if (q.IsEmpty()) {
        std::cerr << "Очередь пуста. Задача прервана.\n";
        return;
    }
    std::cout << "Исходная очередь: ";
    q.Print();
    std::cout << "Адрес начала: " << static_cast<void*>(q.GetHead()) << std::endl;
    std::cout << "Адрес конца: " << static_cast<void*>(q.GetTail()) << std::endl;
    std::cout << "Извлечённые элементы: ";
    int extracted = 0;
    for (int i = 0; i < 5 && !q.IsEmpty(); i++) {
        std::cout << q.Pop() << " ";
        extracted++;
    }
    std::cout << std::endl;
    std::cout << "Очередь пуста? " << (q.IsEmpty() ? "Да" : "Нет") << std::endl;
    std::cout << "Новый адрес начала: " << static_cast<void*>(q.GetHead()) << std::endl;
    std::cout << "Новый адрес конца: " << static_cast<void*>(q.GetTail()) << std::endl;

    if (!q.IsEmpty()) {
        std::cout << "Оставшаяся очередь: ";
        q.Print();
    }
}

// Элементы, кратные 7, в обратном порядке
void ListWork15() {
    std::cout << "\nЗадача 3 ListWork15: Элементы, кратные 7, в обратном порядке.\n";
    List lst = ChooseList("Выберите способ заполнения списка:");
    if (lst.IsEmpty()) {
        std::cerr << "Список пуст. Задача прервана.\n";
        return;
    }
    std::cout << "Исходный список: ";
    lst.Print();
    std::vector<int> multiples;
    TNode* curr = lst.GetHead();
    while (curr) {
        if (curr->data % 7 == 0) {
            multiples.push_back(curr->data);
        }
        curr = curr->next;
    }
    if (multiples.size() < 2) {
        std::cerr << "Ошибка: найдено менее 2 элементов, кратных 7 (найдено "
            << multiples.size() << "). Задача прервана.\n";
        return;
    }
    std::cout << "Элементы, кратные 7, в обратном порядке: ";
    for (int i = multiples.size() - 1; i >= 0; i--) {
        std::cout << multiples[i] << " ";
    }
    std::cout << std::endl;
}

// Вставить M после каждого 4-го элемента 
void ListWork24() {
    std::cout << "\nЗадача 4 ListWork24: Вставка M после каждого 4-го элемента.\n";
    List lst = ChooseList("Выберите способ заполнения списка:");
    if (lst.IsEmpty()) {
        std::cerr << "Список пуст. Задача прервана.\n";
        return;
    }
    std::cout << "Исходный список: ";
    lst.Print();
    int M;
    std::cout << "Введите значение M для вставки: ";
    std::cin >> M;
    lst.InsertAfter(M);
    TNode* last = lst.GetHead();
    if (last) {
        while (last->next) last = last->next;
    }
    std::cout << "Список после вставок: ";
    lst.Print();
    std::cout << "Указатель на последний элемент: " << static_cast<void*>(last) << std::endl;
    if (last) {
        std::cout << "Значение последнего элемента: " << last->data << std::endl;
    }
}

// Упорядоченный по убыванию список из файла
void ListWork62() {
    std::cout << "\nЗадача 5 ListWork62: Упорядоченный по убыванию список из файла\n";
    std::string filename;
    std::cout << "Введите имя файла с данными: ";
    std::cin >> filename;
    List lst = CreateOrderedListFromFile(filename);
    if (lst.IsEmpty()) {
        std::cerr << "Не удалось создать список из файла.\n";
        return;
    }
    std::cout << "Упорядоченный по убыванию список: ";
    lst.Print();
}