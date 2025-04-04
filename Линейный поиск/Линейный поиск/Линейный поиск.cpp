#include <iostream>
#include <clocale>
using namespace std;

int LineSearch(int mas[], int key, const int n) { // функция линейного поиска
    int cnt = 0;

    for (int i = 0; i < n; i++) { // прохождение по всем элементам массива
        if (mas[i] == key) {        // сравнение с ключом
            cnt += 1;                // увеличение счётчика на +1 если найден элемент равный ключу
        }
    }
    return cnt;
}
int main() {
    setlocale(LC_ALL,"ru");
    const int n = 9;
    int mas[n] = { 8, 0, 12, -74, 85, 12, 4, 7, 12 };
    int key;
    cout << "Исходный массив: ";
    for (int i = 0; i < n; i++) {
        cout << mas[i] << ' ';
    }
    cout << endl << "Введите ключ: ";
    cin >> key;
    cout << "Ответ: " << LineSearch(mas, key, n);
}

