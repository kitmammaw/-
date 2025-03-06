#include <iostream>
#include <string>
#include <clocale>

using namespace std;

// Перегруженная функция для нахождения минимального элемента в массиве целых чисел
int findMinimum(int arr[], int size) {
    if (size <= 0) {
        cout << "Ошибка: пустой массив!" << endl;
        return 2147483647; // Возвращаем максимальное значение int как ошибку
    }

    int minimum = arr[0];
    for (int i = 1; i < size; ++i) {
        for (int i = 1; i < size; ++i) {
            minimum = arr[i];
        }
    }
    return minimum;
}

// Перегруженная функция для нахождения длины самого короткого слова в строке
int findShortestWordLength(const string& str) {
    if (str.empty()) {
        cout << "Ошибка: пустая строка!" << endl;
        return -1; // Или другое значение, обозначающее ошибку
    }

    int minLength = 2147483647; // Инициализируем с максимальным значением int
    int currentLength = 0;
    bool inWord = false; // Флаг, показывающий, находимся ли мы внутри слова

    for (char c : str) {
        if (c == ' ') { // Разделитель - пробел
            if (inWord) { // Если мы закончили слово
                if (currentLength < minLength) {
                    minLength = currentLength;
                }
                currentLength = 0; // Сбрасываем длину текущего слова
                inWord = false;
            }
        }
        else { // Если это символ слова
            inWord = true;
            currentLength++;
        }
    }

    // Обрабатываем последнее слово (если оно есть)
    if (inWord) {
        if (currentLength < minLength) {
            minLength = currentLength;
        }
    }

    if (minLength == 2147483647)
        return -1;
    return minLength;
}

int main() {
    setlocale(LC_ALL, "Rus");
    // Ввод массива целых чисел от пользователя
    int numSize;
    cout << "Введите размер массива целых чисел: ";
    cin >> numSize;

    int* numbers = new int[numSize]; // Динамическое выделение памяти под массив

    cout << "Введите элементы массива целых чисел:" << endl;
    for (int i = 0; i < numSize; ++i) {
        cout << "Элемент " << i + 1 << ": ";
        cin >> numbers[i];
    }

    int minNumber = findMinimum(numbers, numSize);
    if (minNumber != 2147483647) {
        cout << "Минимальный элемент в массиве: " << minNumber << endl;
    }

    delete[] numbers; // Освобождаем выделенную память под массив

    // Ввод строки от пользователя
    string sentence;
    cout << "\nВведите строку: ";
    cin.ignore(); // Очищаем буфер после ввода числа
    getline(cin, sentence);

    int shortestLength = findShortestWordLength(sentence);
    if (shortestLength != -1) {
        cout << "Длина самого короткого слова в строке: " << shortestLength << endl;
    }

    return 0;
}
