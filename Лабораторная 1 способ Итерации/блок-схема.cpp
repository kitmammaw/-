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
	return sin(sqrt(1 - 0.4 * pow(sin(asin(x)), 2)));
}
double C(double x)
{
	return (-sqrt(5) * sin(2 * x)) / 5 * sqrt(5 - 2 * pow(sin(x), 2));
}

int main()
{
	setlocale(LC_ALL, "Rus");
	float a, b, x0, x1;
	float e = 0.00001;
	cout << "������� ������� ��������� � � b: ";
	cin >> a >> b;
	if (abs(C(b))<1)
	{
		x0 = b;
		cout << "�0= " << x0 << endl;
	}
	else
	{
		x0 = a;
		cout << "�0= " << x0 << endl;
	}
	x1 = B(x0);
	cout << "������ �����������: " << (x1) << endl;
	while (fabs(x1 - x0) > e)
	{
		x0 = x1;
		x1 = B(x0);
		cout << (x1) << endl;
	}
	cout << "�����: " << (x1);
	return 0;
}