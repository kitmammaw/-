#include <iostream>
#include <clocale>
using namespace std;

const int MAX_DISKS = 10; // Максимальное количество дисков

// Функция для отображения текущего состояния башен
void printTowers(int towers[3][MAX_DISKS], int numDisks) 
{
    for (int level = numDisks - 1; level >= 0; --level) 
    {
        for (int tower = 0; tower < 3; ++tower) 
        {
            int diskSize = towers[tower][level];
            // Вычисляем количество пробелов и звездочек
            int spaces = numDisks - diskSize;
            int stars = diskSize;

            // Печатаем пробелы
            for (int i = 0; i < spaces; ++i) cout << " ";
            // Печатаем звездочки
            for (int i = 0; i < stars; ++i) cout << "*";
            // Печатаем центр башни
            cout << "|";
            // Печатаем звездочки
            for (int i = 0; i < stars; ++i) cout << "*";
            // Печатаем пробелы
            for (int i = 0; i < spaces; ++i) cout << " ";
            cout << " ";
        }
        cout << endl;
    }
    // Печатаем разделитель
    for (int i = 0; i < numDisks * 6; ++i) cout << "-";
    cout << endl << endl;
}

// Функция для поиска верхнего диска на башне
int findTopDisk(int tower[MAX_DISKS], int numDisks) {
    for (int i = numDisks - 1; i >= 0; --i) {
        if (tower[i] != 0) return i;
    }
    return -1; // Башня пуста
}

// Рекурсивная функция для решения Ханойской башни
void hanoi(int n, int towers[3][MAX_DISKS], int from, int to, int aux, int numDisks) {
    if (n == 0) return;

    // Перемещаем n-1 дисков с from на aux
    hanoi(n - 1, towers, from, aux, to, numDisks);

    // Находим верхний диск на башне from
    int fromTop = findTopDisk(towers[from], numDisks);
    if (fromTop == -1) return; // Если башня пуста, ничего не делаем
    int diskSize = towers[from][fromTop];

    // Находим верхний диск на башне to
    int toTop = findTopDisk(towers[to], numDisks);

    // Проверяем, можно ли переместить диск
    if (toTop == -1 || towers[to][toTop] > diskSize) {
        // Перемещаем диск на башню to
        towers[to][toTop + 1] = diskSize;
        towers[from][fromTop] = 0;

        // Выводим текущее состояние башен
        printTowers(towers, numDisks);
    }
    else {
        cout << "Ошибка: Невозможно переместить диск " << diskSize << " на диск " << towers[to][toTop] << endl;
        return;
    }

    // Перемещаем n-1 дисков с aux на to
    hanoi(n - 1, towers, aux, to, from, numDisks);
}

int main() {
    setlocale(LC_ALL, "Rus");
    int numDisks;

    // Запрашиваем у пользователя количество дисков
    cout << "Введите количество дисков (не более " << MAX_DISKS << "): ";
    cin >> numDisks;

    // Инициализация башен
    int towers[3][MAX_DISKS] = { 0 }; // Все башни изначально пусты

    // Инициализация начального состояния башен
    for (int i = 0; i < numDisks; ++i) {
        towers[0][i] = numDisks - i;
    }

    // Решаем задачу Ханойской башни
    hanoi(numDisks, towers, 0, 2, 1, numDisks);

    return 0;
}