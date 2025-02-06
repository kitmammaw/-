#include <iostream>
using namespace std;
int main()
{
	setlocale(LC_ALL, "Rus");
	int tmp;
	const int n = 7;
	// Заполнение массива случайными числами
	int arr[n];
	int range_min, range_max;
	range_min = 2;
	range_max = 412;
	for (int i = 0; i < n; i++)
	{
		arr[i] = ((double)rand() / RAND_MAX) * (range_max -
			range_min) + range_min;
		cout << arr[i] << " ";
	}
	cout << endl;
	// цикл сортировки
	for (int i = 0; i < n - 1; i++) // т.к. пары
	{
		for (int j = 0; j < n - 1 - i; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
		}
		for (int y = 0; y < n; y++)
			cout << arr[y] << " ";
		cout << endl;
	}
	cout << "Отсортированный массив: " << endl;
	for (int i = 0; i < n; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
	return 0;
}
