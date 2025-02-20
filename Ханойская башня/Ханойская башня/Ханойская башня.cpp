#include <iostream>

using namespace std;

// Функция для решения головоломки Ханойской башни
// n: количество дисков
// source: исходный шест (A, B или C)
// destination: целевой шест (A, B или C)
// auxiliary: вспомогательный шест (A, B или C)
void hanoiTower(int n, char source, char destination, char auxiliary) {
    if (n == 1) {
        cout << "Переместить диск 1 с " << source << " на " << destination << endl;
        return;
    }

    // Шаг 1: Переместить n-1 дисков с исходного шеста на вспомогательный шест, используя целевой шест как вспомогательный
    hanoiTower(n - 1, source, auxiliary, destination);

    // Шаг 2: Переместить самый большой диск (n-й диск) с исходного шеста на целевой шест
    cout << "Переместить диск " << n << " с " << source << " на " << destination << endl;

    // Шаг 3: Переместить n-1 дисков с вспомогательного шеста на целевой шест, используя исходный шест как вспомогательный
    hanoiTower(n - 1, auxiliary, destination, source);
}

int main() {
    setlocale(LC_ALL, "Russian");
    int numDisks;

    cout << "Введите количество дисков: ";
    cin >> numDisks;

    // Решить головоломку Ханойской башни для заданного количества дисков
    // Используем шесты A (исходный), B (вспомогательный) и C (целевой)
    hanoiTower(numDisks, 'A', 'C', 'B');

    return 0;
}
