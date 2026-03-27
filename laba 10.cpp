#include <iostream>
#include <vector>
#include <fstream>
#include <Windows.h>
#include "Header.h"

int main() {
    using namespace std;
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    int choice;
    do {
        cout << "    ВЫБОР ЗАДАНИЯ" << endl;
        cout << "1. Dynamic6: Извлечь первые 9 элементов стека" << endl;
        cout << "2. Dynamic28: Извлечь первые 5 элементов очереди" << endl;
        cout << "3. ListWork15: Элементы кратные 7 в обратном порядке" << endl;
        cout << "4. ListWork24: Вставить M после каждого 4-го элемента" << endl;
        cout << "5. ListWork62: Упорядоченный по убыванию список из файла" << endl;
        cout << "0. Выход" << endl;
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
            Dynamic6();
            break;

        case 2:
            Dynamic28();
            break;

        case 3:
            ListWork15();
            break;

        case 4:
            ListWork24();
            break;

        case 5:
            ListWork62();
            break;

        case 0:
            cout << "Программа завершена." << endl;
            break;

        default:
            cout << "Неверный выбор!" << endl;
        }
    } while (choice != 0);

    return 0;
}