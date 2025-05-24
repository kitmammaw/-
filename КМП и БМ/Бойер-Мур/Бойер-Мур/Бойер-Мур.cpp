#include <iostream> 
#include <string> 
#include <clocale> 
using namespace std;

void buildBadCharTable(const string& pattern, int badCharTable[256]) // Функция buildBadCharTable (построение таблицы плохих символов)
{
    int m = pattern.size(); // Получаем длину образа
    for (int i = 0; i < 256; ++i) // Инициализация таблицы значением m
    {
        badCharTable[i] = m; // Присваиваем каждому элементу таблицы значение длины образа
    }
    for (int i = 0; i < m - 1; ++i) // Заполнение таблицы на основе pattern
    {
        badCharTable[(unsigned char)pattern[i]] = m - 1 - i; // Записываем смещение для символа в таблице
    }
    return;
}

int boyerMooreSearch(const string& text, const string& pattern) // Функция поиска алгоритмом Бойера-Мура
{
    int n = text.size(); // Получаем длину текста
    int m = pattern.size(); // Получаем длину образа
    if (m == 0) return -1;  // Проверки на пустые строки и длину - если образ пуст, возвращаем -1
    if (n == 0) return -1;  // Проверки на пустые строки и длину - если текст пуст, возвращаем -1
    if (m > n) return -1;  // Проверки на пустые строки и длину - если образец длиннее текста, возвращаем -1
    int badCharTable[256]; // Таблица плохих символов
    buildBadCharTable(pattern, badCharTable); // Построение таблицы
    int shift = 0; // Смещение
    while (shift <= n - m) // Цикл пока смещение не превышает n-m
    {
        for (int k = 0; k < shift; ++k) // пошаговый вывод
        {
            cout << " ";
        }
        cout << pattern << endl;
        int j = m - 1; // Индекс для pattern (начинаем с конца)
        while (j >= 0 && pattern[j] == text[shift + j]) // Пока j >= 0 и символы совпадают
        {
            j--; // Двигаемся по pattern слева направо
        }
        if (j < 0) // Если образ найден
        {
            cout << "Образец найден на позиции: " << shift << endl;
            return shift;
        }
        else // Если образ не найден
        {
            shift += badCharTable[(unsigned char)text[shift + m - 1]]; // Сдвигаем образ
        }
    }
    cout << "Образец не найден";
    return -1;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    system("chcp 1251");
    system("cls");
    string text, pattern;

    cout << "Введите текст: " << endl;
    getline(cin, text);

    cout << "Введите образец: ";
    getline(cin, pattern);

    boyerMooreSearch(text, pattern);

    return 0;
}
