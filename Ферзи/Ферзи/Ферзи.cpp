#include <iostream>
#include <cmath> // Для abs()

using namespace std;

const int MAX_SIZE = 15; // Максимальный размер доски
const int MAX_SOLUTIONS = 3; // Максимальное количество решений для вывода

// Функция для проверки, является ли позиция безопасной для ферзя
bool isSafe(int row, int col, int queens[MAX_SIZE], int n) {
    for (int i = 0; i < row; ++i) { // Проверяем только предыдущие строки
        int otherRow = i;
        int otherCol = queens[i];

        // Проверка той же колонки
        if (col == otherCol) {
            return false;
        }

        // Проверка диагоналей
        if (abs(row - otherRow) == abs(col - otherCol)) {
            return false;
        }
    }
    return true;
}

// Рекурсивная функция для поиска решений
bool solveNQueens(int row, int n, int queens[MAX_SIZE], int solutions[][MAX_SIZE], int& solutionCount) {
    if (solutionCount >= MAX_SOLUTIONS) {
        return true; // Достаточно решений найдено
    }

    if (row == n) {
        // Найдено решение. Сохраняем его.
        for (int i = 0; i < n; ++i) {
            solutions[solutionCount][i] = queens[i];
        }
        solutionCount++;
        return false; // Продолжаем поиск других решений.
    }

    for (int col = 0; col < n; ++col) {
        if (isSafe(row, col, queens, n)) {
            queens[row] = col; // Поставить ферзя в (row, col)
            solveNQueens(row + 1, n, queens, solutions, solutionCount);

        }
    }
    return false; // Если дошли сюда, значит в этой ветке решений больше нет.
}

// Функция для печати решения
void printSolution(int queens[MAX_SIZE], int n) {
    for (int i = 0; i < n; ++i) {
        for (int k = 0; k < n; ++k) {
            if (queens[i] == k) {
                cout << "1 ";
            }
            else {
                cout << "0 ";
            }
        }
        cout << endl;
    }
    cout << endl;
}

int main() {
    setlocale(LC_ALL, "Rus");
    int n = 8; // Размер доски
    int queens[MAX_SIZE]; // Массив для хранения колонн, где находятся ферзи в каждой строке
    int solutions[MAX_SOLUTIONS][MAX_SIZE]; // Массив для хранения до MAX_SOLUTIONS решений
    int solutionCount = 0; // Количество найденных решений

    solveNQueens(0, n, queens, solutions, solutionCount);

    if (solutionCount > 0) {
        cout << "Найдено " << solutionCount << " решений для задачи о " << n << " ферзях." << endl;

        int numSolutionsToPrint = min(solutionCount, MAX_SOLUTIONS);

        for (int i = 0; i < numSolutionsToPrint; ++i) {
            cout << "Решение " << i + 1 << ":" << endl;
            printSolution(solutions[i], n);
        }
    }

    return 0;
}