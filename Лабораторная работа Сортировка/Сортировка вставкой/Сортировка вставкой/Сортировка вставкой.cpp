#include <iostream>
using namespace std;
int main()
{
	setlocale(LC_ALL, "Rus");
	int tmp;
	const int n = 7;
	// Заполнение массива случайными числами
	// возьмите из другого примера любого

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
	int key; // переменная для хранения значения элемента, с которым мы сравниваем текущий
		// цикл сортировки
		for (int i = 0; i < n; i++)
		{
			key = arr[i];
			int j = i - 1;
			// если условие выполняется, нам нужно обменять элементы
				while (j >= 0 && arr[j] > key)
				{
					arr[j + 1] = arr[j];
					j--;
				}
			arr[j + 1] = key;
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