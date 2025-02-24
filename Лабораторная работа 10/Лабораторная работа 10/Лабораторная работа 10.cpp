#include <iostream>
#include <string>
#include <clocale>
    using namespace std;

    int main() {
        setlocale(LC_ALL, "Rus");
        system("chcp 1251");
        system("cls");
        int size;

        cout << "Введите количество строк: ";
        cin >> size;

        // Выделяем память для массива строк
        string* strings = new string[size];

        // Вводим строки от пользователя
        cout << "Введите строки:" << endl;
        cin.ignore(); // Очищаем буфер после ввода числа

        for (int i = 0; i < size; ++i) {
            cout << "Строка " << i + 1 << ": ";
            getline(cin, strings[i]); // Используем getline для ввода строк с пробелами
        }

        cout << "\nИсходный массив:" << endl;
        for (int i = 0; i < size; ++i) {
            cout << strings[i] << endl;
        }

        // Удаление строк, начинающихся и заканчивающихся на "а"
        int newSize = 0; // Новый размер массива после удаления
        string* tempStrings = new string[size]; // Временный массив

        for (int i = 0; i < size; ++i) {
            if (!strings[i].empty() && strings[i][0] == 'а' && strings[i].back() == 'а') {
                // Не копируем строку, начинающуюся и заканчивающуюся на 'а'
                continue;
            }
            tempStrings[newSize] = strings[i];
            newSize++;
        }

        // Освобождаем память, выделенную под старый массив
        delete[] strings;

        // Переназначаем указатель на новый массив
        strings = tempStrings;
        size = newSize;

        cout << "\nМассив после удаления строк, начинающихся и заканчивающихся на 'а':" << endl;
        for (int i = 0; i < size; ++i) {
            cout << strings[i] << endl;
        }

        // Освобождаем выделенную память
        delete[] strings;
        strings = nullptr;

        return 0;
    }




