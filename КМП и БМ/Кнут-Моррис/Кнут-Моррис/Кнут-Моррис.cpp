#include <iostream>
#include <clocale>
#include <string>
using namespace std;

// Вычисляет LPS-массив для KMP
void computeLPSArray(string pattern, int M, int* lps)
{
    int len = 0; // Длина самого длинного префикса, который также является суффиксом
    lps[0] = 0; // Первый элемент LPS-массива всегда 0
    int i = 1; // Индекс для прохода по строке pattern
    while (i < M) // Цикл пока индекс i меньше длины строки pattern (M)
    {
        if (pattern[i] == pattern[len]) // Если i-ый символ в pattern равен len-ому символу 
        {
            len++; // Увеличиваем длину 
            lps[i] = len; // Записываем новую длину 
            i++; // Увеличиваем индекс
        }
        else //если символы не совпадают
        {
            if (len != 0) // Если len не равно 0 (уже есть префикс)
            {
                len = lps[len - 1]; // "Откат" к предыдущему более короткому префиксу
            }
            else // если нет префикса
            {
                lps[i] = 0; //присваиваем 0
                i++; // увеличиваем индекс
            }
        }
    }
}

// Поиск подстроки с использованием алгоритма Кнута-Морриса-Пратта (KMP)
void KMPSearch(string pattern, string text)
{
    int M = pattern.length(); // длина строки 
    int N = text.length(); // длина образа
    int* lps = new int[M]; //дин память для лпс массива
    computeLPSArray(pattern, M, lps); // вычисляем лпс массив
    int i = 0;  // Индекс для text[]
    int j = 0;  // Индекс для pattern[]
    bool f = false; // флаг показывающий найден образец хотя бы раз 
    while (i < N) // Цикл пока индекс i меньше длины строки text (N)
    {
        for (int k = 0; k < i - j; k++) // визуализация как двигается образец
        {
            cout << " ";
        }
        cout << pattern << endl;

        if (pattern[j] == text[i])  // если символы совпадабт 
        {
            j++; // увеличиваем индексы
            i++;
        }
        else if (i < N && pattern[j] != text[i]) // Если символы не совпадают и i < N
        {
            if (j != 0) // Если j не равно 0 (было частичное совпадение)
            {
                j = lps[j - 1]; // Используем LPS-массив для сдвига образца
            }
            else // нет совпадений 
            {
                i++; // увеличиваем индекс 
            }
        }

        if (j == M) // если образец найден 
        {
            cout << "Образец найден на позиции: " << i - j << endl;
            j = lps[j - 1];
            f = true;
        }
    }
    if (!f)  // если образец не найден 
    {
        cout << "Образ не найден";
    }
    delete[] lps;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    system("chcp 1251");
    system("cls");
    string text, pattern;

    cout << "Введите текст: " << endl;
    getline(cin, text);

    cout << "Введите образ: ";
    getline(cin, pattern);

    KMPSearch(pattern, text);

    return 0;
}
