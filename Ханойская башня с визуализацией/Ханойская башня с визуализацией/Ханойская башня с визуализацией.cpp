#include <iostream>
#include <clocale>
using namespace std;

const int MAX_DiskKS = 10; // Максимальное количество дисков

void printState(int DiskksOnBar[3][MAX_DiskKS])
{
    cout << "Текущее состояние стержней:" << endl;
    for (int i = 0; i < 3; ++i) 
    {
        cout << "Стержень " << (i + 1) << ": ";
        for (int j = 0; j < MAX_DiskKS; ++j) 
        {
            if (DiskksOnBar[i][j] != 0) 
            {
                cout << DiskksOnBar[i][j] << " ";
            }
        }
        cout << endl;
    }
    cout << endl;
}

void hanoiTower(int n, int start, int finish, int help, int DiskksOnBar[3][MAX_DiskKS])
{
    if (n > 0)
    {
        hanoiTower(n - 1, start, help, finish, DiskksOnBar);

        // Перемещение диска
        // Находим первый свободный индекс на целевом стержне
        int finishIndex = MAX_DiskKS - 1;
        while (finishIndex >= 0 && DiskksOnBar[finish - 1][finishIndex] != 0)
        {
            finishIndex--;
        }

        // Находим индекс диска на исходном стержне
        int startIndex = 0;
        while (startIndex < MAX_DiskKS && DiskksOnBar[start - 1][startIndex] != n)
        {
            startIndex++;
        }

        if (startIndex < MAX_DiskKS)
        { //Проверка на случай, если диск не найден (чтобы избежать ошибок)
            // Перемещаем диск
            DiskksOnBar[finish - 1][finishIndex] = n; // Помещаем диск на целевой стержень
            DiskksOnBar[start - 1][startIndex] = 0; // Убираем диск с исходного стержня

            cout << "Переместить диск " << n << " с стержня " << start << " на стержень " << finish << endl;
            printState(DiskksOnBar); // Печатаем текущее состояние стержней

            hanoiTower(n - 1, help, finish, start, DiskksOnBar);
        }
        else
        {
            cerr << "Ошибка: Диск " << n << " не найден на стержне " << start << endl;
        }
    }
}

int main()
{
    int Disk;
    setlocale(LC_ALL, "Rus");

    cout << "Введите количество дисков: ";
    cin >> Disk;

    // Инициализация состояния стержней
    int DiskksOnBar[3][MAX_DiskKS] = { 0 }; // 0 означает, что диск отсутствует
    for (int i = 0; i < Disk; ++i)
    {
        DiskksOnBar[0][MAX_DiskKS - 1 - i] = i + 1; // Заполняем первый стержень дисками
    }

    cout << "Решение Ханойской башни с " << Disk << " дисками:" << endl;
    printState(DiskksOnBar); // Печатаем начальное состояние
    hanoiTower(Disk, 1, 3, 2, DiskksOnBar); // Перемещение дисков с стержня 1 на стержень 3, используя стержень 2 в качестве вспомогательного

    return 0;
}