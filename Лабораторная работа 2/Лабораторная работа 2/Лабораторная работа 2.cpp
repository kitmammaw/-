#include <iostream> 
#include <cmath> 
#include <iomanip> 

using namespace std;

double f_exact(double x) {
	return exp(2 * x);
}

double recursive(double x, int n, double e) {
	return e * (2 * x) / n;
}

double power(double x, int n) {
	double sum = 1; // Начальное значение для рекурсии (S = 1) 
	double term = 2 * x; // Первый член 
	for (int i = 1; i <= n; ++i) {
		sum += term;
		term = recursive(x, i + 1, term);
	}
	return sum;
}

int main() {
	double a = 0.1;
	double b = 1.0;
	int k = 10;
	int n = 20;
	double step = (b - a) / k;

	cout << fixed << setprecision(6);
	for (double x = a; x <= b; x += step) {
		double Sn = power(x, n);
		double Se = power(x, n); // Для совместимости формата вывода 
		double y = f_exact(x);

		cout << "x= " << x << " Sn = " << Sn << " Se = " << Se << " y = " << y << endl;
	}

	return 0;
}