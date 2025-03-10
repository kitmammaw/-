#include <iostream>
#include <fstream>
#include <cstring>
#include <clocale>

using namespace std;

// Структура "Фильм"
struct Film {
    char title[50];      // Название
    char director[50];   // Режиссер
    char country[50];    // Страна
    double profit;       // Прибыль
};

// Функция для вывода информации о фильме
void printFilm(const Film& film) {
    cout << "Название: " << film.title << endl << "Режиссер: " << film.director << endl
        << "Страна: " << film.country << endl << "Прибыль: " << film.profit << endl << endl;
}

// Функция для формирования двоичного файла
void createBinaryFile(const char* filename, Film* films, int count) {
    ofstream outFile(filename, ios::binary);
    if (!outFile) {
        cerr << "Ошибка открытия файла для записи!" << endl;
        return;
    }
    outFile.write((char*)films, count * sizeof(Film));
    outFile.close();
}

// Функция для печати содержимого двоичного файла
void printBinaryFile(const char* filename) {
    ifstream inFile(filename, ios::binary);
    if (!inFile) {
        cerr << "Ошибка открытия файла для чтения!" << endl;
        return;
    }
    Film film;
    while (inFile.read((char*)&film, sizeof(Film))) {
        printFilm(film);
    }
    inFile.close();
}

// Функция для удаления последних 2 элементов из файла
void deleteLastTwoElements(const char* filename) {
    ifstream inFile(filename, ios::binary);
    if (!inFile) {
        cerr << "Ошибка открытия файла для чтения!" << endl;
        return;
    }

    // Определяем количество элементов в файле
    inFile.seekg(0, ios::end);
    int fileSize = inFile.tellg();
    int count = fileSize / sizeof(Film);
    inFile.seekg(0, ios::beg);

    if (count < 2) {
        cerr << "В файле меньше 2 элементов!" << endl;
        inFile.close();
        return;
    }

    // Читаем все элементы, кроме последних двух
    Film* films = new Film[count - 2];
    inFile.read((char*)films, (count - 2) * sizeof(Film));
    inFile.close();

    // Перезаписываем файл без последних двух элементов
    ofstream outFile(filename, ios::binary);
    if (!outFile) {
        cerr << "Ошибка открытия файла для записи!" << endl;
        delete[] films;
        return;
    }
    outFile.write((char*)films, (count - 2) * sizeof(Film));
    outFile.close();

    delete[] films;
}

// Функция для добавления элемента после элемента с указанным названием
void addElementAfterTitle(const char* filename, const char* title, const Film& newFilm) {
    ifstream inFile(filename, ios::binary);
    if (!inFile) {
        cerr << "Ошибка открытия файла для чтения!" << endl;
        return;
    }

    // Определяем количество элементов в файле
    inFile.seekg(0, ios::end);
    int fileSize = inFile.tellg();
    int count = fileSize / sizeof(Film);
    inFile.seekg(0, ios::beg);

    // Читаем все элементы
    Film* films = new Film[count + 1]; // +1 для нового элемента
    inFile.read((char*)films, count * sizeof(Film));
    inFile.close();

    // Ищем элемент с указанным названием
    bool found = false;
    int insertIndex = -1;
    for (int i = 0; i < count; ++i) {
        if (strcmp(films[i].title, title) == 0) {
            found = true;
            insertIndex = i + 1;
            break;
        }
    }

    if (!found) {
        cerr << "Элемент с названием \"" << title << "\" не найден!" << endl;
        delete[] films;
        return;
    }

    // Сдвигаем элементы вправо, начиная с insertIndex
    for (int i = count; i > insertIndex; --i) {
        films[i] = films[i - 1];
    }

    // Вставляем новый элемент
    films[insertIndex] = newFilm;

    // Перезаписываем файл
    ofstream outFile(filename, ios::binary);
    if (!outFile) {
        cerr << "Ошибка открытия файла для записи!" << endl;
        delete[] films;
        return;
    }
    outFile.write((char*)films, (count + 1) * sizeof(Film));
    outFile.close();

    delete[] films;
}

int main() {
    setlocale(LC_ALL, "Rus");
    const char* filename = "films.bin";

    // Данные для формирования файла
    Film films[] = {
        {"Inception", "Christopher Nolan", "USA", 829.9},
        {"Interstellar", "Christopher Nolan", "USA", 677.5},
        {"The Dark Knight", "Christopher Nolan", "USA", 1004.9}
    };
    int count = sizeof(films) / sizeof(Film);

    // Формируем двоичный файл
    createBinaryFile(filename, films, count);

    // Печатаем содержимое файла
    cout << "Содержимое файла:" << endl;
    printBinaryFile(filename);

    // Удаляем последние 2 элемента
    deleteLastTwoElements(filename);
    cout << "\nПосле удаления последних 2 элементов:" << endl;
    printBinaryFile(filename);

    // Добавляем новый элемент после элемента с указанным названием
    Film newFilm = { "Dunkirk", "Christopher Nolan", "UK", 525.0 };
    addElementAfterTitle(filename, "Inception", newFilm);
    cout << "\nПосле добавления нового элемента:" << endl;
    printBinaryFile(filename);

    return 0;
}