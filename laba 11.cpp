#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>
#include <Windows.h>
#include "Header.h"

int main() {
    using namespace std;
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    srand(time(0));
    int choice;
    do {
        cout << "\n    ВЫБОР ЗАДАНИЯ \n";
        cout << "1. ListWork69: Циклический список с шагом k\n";
        cout << "2. ListWork42: Циклический двусвязный список (удаление)\n";
        cout << "3. ListWork65: Вывод в файл (последний, первый, предпоследний...)\n";
        cout << "4. ListWork48: Список с барьером (присвоить 0 нечетным)\n";
        cout << "5. Считалочка (имена детей)\n";
        cout << "0. Выход\n";
        cout << "Выбор: ";
        cin >> choice;
        if (cin.fail()) {
            cin.clear();
            cin.ignore();
            cout << "Ошибка ввода! /n";
            continue;
        }
        switch (choice) {
        case 1:
            ListWork69();
            break;
        case 2:
            ListWork42();
            break;
        case 3:
            ListWork65();
            break;
        case 4:
            ListWork48();
            break;
        case 5:
            ChildrenGame();
            break;
        case 0:
            cout << "Программа завершена." << endl;
            break;
        default:
            cout << "Неверный выбор!" << endl;
        }
    } while (choice != 0);
}