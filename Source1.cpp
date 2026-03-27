#include "Header.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <Windows.h>

//обраюотка заполнения
DoubleList ChooseDoubleList(const std::string& prompt) {
    std::cout << prompt << std::endl;
    std::cout << "1. С консоли\n2. Из файла\n3. Рандом\nВыбор: ";
    int choice;
    std::cin >> choice;
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore();
        std::cout << "Ошибка ввода! /n";
    }
    DoubleList list;
    std::string filename;
    switch (choice) {
    case 1: {
        int n;
        std::cout << "Введите количество элементов: ";
        std::cin >> n;
        std::cout << "Введите " << n << " целых чисел: ";
        for (int i = 0; i < n; i++) {
            int val;
            std::cin >> val;
            list.PushBack(val);
        }
        break;
    }
    case 2: {
        std::cout << "Введите имя файла: ";
        std::cin >> filename;
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Ошибка открытия файла.\n";
            return list;
        }
        int val;
        while (file >> val) {
            list.PushBack(val);
        }
        file.close();
        break;
    }
    case 3: {
        int n;
        std::cout << "Введите количество случайных элементов: ";
        std::cin >> n;
        for (int i = 0; i < n; i++) {
            list.PushBack(rand() % 100);
        }
        break;
    }
    default:
        std::cerr << "Неверный выбор. Возвращён пустой список.\n";
    }
    return list;
}

//обраюотка заполнения
CircularList ChooseCircularList(const std::string& prompt) {
    std::cout << prompt << std::endl;
    std::cout << "1. С консоли\n2. Из файла\n3. Рандом\nВыбор: ";
    int choice;
    std::cin >> choice;
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore();
        std::cout << "Ошибка ввода! /n";
    }
    CircularList list;
    std::string filename;
    switch (choice) {
    case 1: {
        int n;
        std::cout << "Введите количество элементов: ";
        std::cin >> n;
        std::cout << "Введите " << n << " целых чисел: ";
        for (int i = 0; i < n; i++) {
            int val;
            std::cin >> val;
            list.PushBack(val);
        }
        break;
    }
    case 2: {
        std::cout << "Введите имя файла: ";
        std::cin >> filename;
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Ошибка открытия файла.\n";
            return list;
        }
        int val;
        while (file >> val) {
            list.PushBack(val);
        }
        file.close();
        break;
    }
    case 3: {
        int n;
        std::cout << "Введите количество случайных элементов: ";
        std::cin >> n;
        for (int i = 0; i < n; i++) {
            list.PushBack(rand() % 100);
        }
        break;
    }
    default:
        std::cerr << "Неверный выбор. Возвращён пустой список.\n";
    }
    return list;
}

//обраюотка заполнения
BarrierList ChooseBarrierList(const std::string& prompt) {
    DoubleList temp = ChooseDoubleList(prompt);
    return BarrierList(temp);
}

// ListWork42: Циклический двусвязный список - удалить элементы, у которых соседи совпадают
void ListWork42() {
    std::cout << "\nListWork42: Циклический двусвязный список\n";
    DoubleList temp = ChooseDoubleList("Выберите способ заполнения двусвязного списка:");
    if (temp.IsEmpty()) {
        std::cerr << "Список пуст. Задача прервана.\n";
        return;
    }
    CircularDoubleList list(temp);
    std::cout << "Исходный циклический список: ";
    list.PrintCircular();
    std::cout << "Количество элементов в циклическом списке: " << list.Count() << std::endl;
    list.DeleteBecauseOfEquals();
    std::cout << "\nСписок после удаления: ";
    if (!list.IsEmpty()) {
        list.PrintCircular();
        std::cout << "Осталось элементов: " << list.Count() << std::endl;
    }
    else {
        std::cout << "Список стал пустым" << std::endl;
    }
}

// ListWork48: Список с барьерным элементом - присвоить 0 нечетным элементам
void ListWork48() {
    std::cout << "\n ListWork48: Список с барьерным элементом \n";
    BarrierList list = ChooseBarrierList("Выберите способ заполнения списка:");
    if (list.GetBarrier()->next == list.GetBarrier()) {
        std::cerr << "Список пуст. Задача прервана.\n";
        return;
    }
    std::cout << "Исходный список (барьерный элемент = 0 в начале и конце): ";
    list.Print();
    std::cout << "Адрес барьерного элемента: " << static_cast<void*>(list.GetBarrier()) << std::endl;
    std::cout << "Адрес текущего элемента: " << static_cast<void*>(list.GetCurrent()) << std::endl;
    std::cout << "Количество элементов: " << list.Count() << std::endl;
    list.AssignZero();
}

// ListWork65: Двусвязный линейный список - вывод в файл (последний, первый, предпоследний, второй...)
void ListWork65() {
    std::cout << "\n ListWork65: \n";
    DoubleList list = ChooseDoubleList("Выберите способ заполнения двусвязного списка:");
    if (list.IsEmpty()) {
        std::cerr << "Список пуст. Задача прервана.\n";
        return;
    }
    std::cout << "Исходный список: ";
    list.Print();
    std::cout << "Количество элементов: " << list.Count() << std::endl;
    std::string filename;
    std::cout << "Введите имя файла для сохранения результата: ";
    std::cin >> filename;

    list.PrintFileAfterBefor(filename);
}

// ListWork69: Циклический список с шагом k
void ListWork69() {
    std::cout << "\n ListWork69: Циклический список с шагом k \n";
    CircularList list = ChooseCircularList("Выберите способ заполнения циклического списка:");
    if (list.IsEmpty()) {
        std::cerr << "Список пуст. Задача прервана.\n";
        return;
    }
    std::cout << "Исходный список: ";
    if (!list.IsEmpty()) {
        TNode* curr = list.GetHead();
        std::cout << curr->data;
        curr = curr->next;
        while (curr != list.GetHead()) {
            std::cout << " -> " << curr->data;
            curr = curr->next;
        }
        std::cout << " (замкнуто)" << std::endl;
    }
    int k;
    std::cout << "Введите шаг k: ";
    std::cin >> k;
    std::string filename;
    std::cout << "Введите имя файла для сохранения результата: ";
    std::cin >> filename;
    list.PrintToFileWithStep(filename, k);
}

// ChildrenGame: Считалка с именами детей
void ChildrenGame() {
    std::cout << "\n Считалка (имена детей) \n";
    ChildrenCircle circle;
    std::string childrenFile;
    std::cout << "Введите имя файла с именами детей: ";
    std::cin >> childrenFile;
    if (!circle.LoadChildrenFromFile(childrenFile)) {
        std::cerr << "Не удалось загрузить имена детей. Задача прервана.\n";
        return;
    }
    std::cout << "\nЗагруженные дети:\n";
    circle.Print();
    std::cout << "Всего детей: " << circle.Count() << std::endl;
    std::string outputFile;
    std::cout << "\nВведите имя выходного файла для результатов: ";
    std::cin >> outputFile;
    circle.SolveGame(outputFile);
}