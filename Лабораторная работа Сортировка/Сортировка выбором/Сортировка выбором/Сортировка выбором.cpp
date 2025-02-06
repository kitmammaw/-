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

	int min_index; // индекс (текущий) наименьшего по значению элемента
		// цикл сортировки
		for (int i = 0; i < n - 1; i++) // 1 элемент в итоге почти сразу будет на своем месте, нет необходимости избыточной итерации
		{
		min_index = i;
		cout << arr[i] << " ";
		for (int j = i + 1; j < n; j++)
		{
		if (arr[j] < arr[min_index])
		{
		min_index = j;
		cout << endl << arr[j] << " ";
		}
		}
		tmp = arr[min_index];
		arr[min_index] = arr[i];
		arr[i] = tmp;
		for (int y = 0; y < n; y++)
			cout << arr[y] << " ";
		cout << endl;
		}
		cout << endl <<"Отсортированный массив: " << endl;
	for (int i = 0; i < n; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
	return 0;
}