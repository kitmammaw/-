#include <iostream>
#include <cstring>
#include<math.h>
using namespace std;

int f(int x)
{
    return 5 * sin(0.5 * x) + 5;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    system("chcp 1251");
    system("cls");
    cout << "Введите предложение: ";
    size_t len = 1; // Начальный размер строки
    char* string = new char[len];
    string[0] = '\0'; // Инициализируем пустую строку
    char Sim;
    while (cin.get(Sim))
    {
        if (Sim == '\n') // Правильная проверка символа новой строки
        {
            break;
        }
        // Увеличиваем размер строки
        char* stringBuf = new char[len + 1]; // Выделяем новую память
        strcpy_s(stringBuf, len + 1, string); // Копируем старую строку
        stringBuf[len - 1] = Sim; // Добавляем новый символ
        stringBuf[len] = '\0'; // Завершаем строку
        delete[] string; // Удаляем старую строку
        string = stringBuf; // Переназначаем указатель
        len++; // Увеличиваем длину строки
    }
    char** matrix = new char* [11]; // создание динамической матрицы 
    for (int i = 0; i < 11; i++)
    {
        matrix[i] = new char[len];
    }
    for (int i = 0; i < 11; i++) //заполнение элементов матрицы пробелами
    {
        for (int j = 0; j < len; j++)
            matrix[i][j] = ' ';
    }
    for (int x = 0; x < len; x++) // распределение сообщения по графику синусоиды
    {
        int y = f(x);
        matrix[y][x] = string[x];
    }
    cout << endl; //вывод матрицы
    for (int i = 0; i < 11; i++)
    {
        for (int j = 0; j < len; j++)
        {
            cout << matrix[i][j];
        }
        cout << endl;
    }
    delete[] string; // очистка памяти
    delete[] matrix;
    return 0;
}
