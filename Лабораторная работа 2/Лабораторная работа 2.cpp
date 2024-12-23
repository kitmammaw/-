#include <cmath>
#include <iomanip>
#include <iostream>

using namespace std;

// Вычисляет точное значение функции
double exactFunction(double x)
{
    return exp(2 * x);
}

// Рекурсивный расчёт текущего члена ряда
double recursiveTerm(double x, int n, double prevTerm)
{
    return prevTerm * (2 * x) / n;
}

// Вычисляет сумму ряда рекурсивным способом с ограничением по числу членов
double powerSeriesRecursive(double x, int n, int current = 1, double term = 1, double sum = 1)
{
    if (current > n)
    {
        return sum;
    }

    double nextTerm = recursiveTerm(x, current, term);
    return powerSeriesRecursive(x, n, current + 1, nextTerm, sum + nextTerm);
}

// Вычисляет сумму ряда с заданной точностью
double powerSeriesWithEpsilon(double x, double epsilon, int current = 1, double term = 1, double sum = 1)
{
    if (fabs(term) < epsilon)
    {
        return sum;
    }

    double nextTerm = recursiveTerm(x, current, term);
    return powerSeriesWithEpsilon(x, epsilon, current + 1, nextTerm, sum + nextTerm);
}

int main()
{
    // Константы диапазона, количества шагов, точности и числа членов ряда
    const double start = 0.1;
    const double end = 1.0;
    const int steps = 10;
    const int maxTerms = 20;
    const double epsilon = 0.0001;
    const double stepSize = (end - start) / steps;

    // Заголовок таблицы
    cout << fixed << setprecision(6);
    cout << "  x         Sn          Se          y" << endl;

    // Основной цикл по значениям x
    for (double x = start; x <= end; x += stepSize)
    {
        double seriesSumN = powerSeriesRecursive(x, maxTerms);        // Сумма ряда с числом членов
        double seriesSumE = powerSeriesWithEpsilon(x, epsilon);      // Сумма ряда с заданной точностью
        double exactValue = exactFunction(x);                        // Точное значение функции

        // Выводим результат
        cout << setw(7) << x
            << setw(12) << seriesSumN
            << setw(12) << seriesSumE
            << setw(12) << exactValue << endl;
    }

    return 0;
}