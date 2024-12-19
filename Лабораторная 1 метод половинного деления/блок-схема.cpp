#include <iostream>
#include <cmath>
#include <chrono>
#include <locale>

using namespace std;

double function(double x)
{
    return sqrt(1 - 0.4 * pow(x, 2)) - asin(x);
}

double bisection(double a, double b, double epsilon, int& iteration)
{
    double x = (a + b) / 2;

    cout << "Итерация " << iteration << ": x = " << x << endl;

    if (fabs(b - a) < epsilon || fabs(function(x)) < epsilon)
    {
        return x;
    }
    else if (function(x) * function(a) < 0)
    {
        iteration++;
        return bisection(a, x, epsilon, iteration);
    }
    else
    {
        iteration++;
        return bisection(x, b, epsilon, iteration);
    }
}

int main()
{
    setlocale(LC_ALL, "Rus");
    double a = 0.0;
    double b = 1.0;
    double epsilon = 0.00001;
    int iteration = 1;

    if (function(a) * function(b) >= 0)
    {
        cout << "Нет корней на данном интервале или метод неприменим." << endl;
        return 1;
    }

    auto start = chrono::high_resolution_clock::now();

    double root = bisection(a, b, epsilon, iteration);

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start).count();

    cout << "Корень: " << root << endl;
    cout << "Количество итераций: " << iteration << endl;
    cout << "Затраченное время: " << duration << " микросекунд" << endl;

    return 0;
}