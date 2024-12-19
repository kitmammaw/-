#include <iostream>
#include <clocale>
#include <cmath>
using namespace std;
double A(double x) 
{
	return sqrt(1 - 0.4 * pow(x, 2)) - asin(x);
}
double B(double x)
{
	return (-2 * x / sqrt(25 - 10 * pow(x, 2))) - (1 / sqrt(1 - pow(x, 2)));
}
double C(double x)
{
	return (-1 / sqrt(25 - 10 * pow(x, 2)) * (5 - 2 * pow(x, 2))) - (x / (sqrt(1 - pow(x, 2))) * (1 - pow(x, 2)));
}

int main()
{
	setlocale(LC_ALL, "Rus");
	float a, b, k, x0, x1;
	float e = 0.0001;
	cout << "¬ведите границы интервала а и b: ";
	cin >> a >> b;
	k = A(a) * C(a);
	if (k > 0)
	{
		x0 = a;
		cout << "ѕервый корень х0= " << x0 << endl;
	}
	else
	{
		x0 = b;
		cout << "ѕервый корень х0= " << x0 << endl;
	}
	x1 = x0 - A(x0) / B(x0);
	while (abs(x1 - x0) > e)
	{
		x0 = x1;
		x1 = x0 - A(x0) / B(x0);
		cout << x1 << endl;
	}
	cout << "ќтвет: " << x1;
	return 0;
}