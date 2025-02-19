#include <iostream>
#include <string>
#include <clocale>
using namespace std;

bool checkArrayOrdering(const string& s, int n, char array[][100]) {
    // Проверка на соответствие длины строки размеру массива N x N
    if (s.length() != n * n) {
        cout << "Ошибка: Длина строки не соответствует N^2." << endl;
        return false;
    }

    // Заполнение массива цифрами из строки
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            array[i][j] = s[i * n + j];
        }
    }

    // Проверка порядка возрастания в первом столбце
    for (int i = 0; i < n - 1; ++i) {
        if (array[i][0] >= array[i + 1][0]) {
            return false;
        }
    }

    return true;
}

int main() {

    setlocale(LC_ALL, "Rus");

    string s;
    int n;

    cout << "Введите строку из N^2 цифр: ";
    getline(cin, s);

    cout << "Введите N (размерность массива N x N): ";
    cin >> n;

    if (n <= 0) {
        cout << "Ошибка: N должно быть положительным целым числом." << endl;
        return 1; // Возвращаем код ошибки
    }

    // Объявление и инициализация массива
    char array[100][100];

    if (checkArrayOrdering(s, n, array)) {
        cout << "Первый столбец располагается в порядке возрастания." << endl;

        // Вывод массива в случае расположения в порядке возрастания
        cout << "Массив:" << endl;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                cout << array[i][j] << " ";
            }
            cout << endl;
        }
    }
    else {
        cout << "Первый столбец не располагается в порядке возрастания." << endl;
    }

    return 0;
}

