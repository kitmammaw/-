#include <iostream>
#include <clocale>
using namespace std;

int binarySearchRec(int arr[], const int n, int key)
{
	int left = 0, right = n - 1;
	while (left <= right)
	{
		int mid = (left + right) / 2;
		if (arr[mid] == key)
		{
			return mid;
		}
		else
		{
			if (arr[mid] < key)
			{
				left = mid + 1;
			}
			else
			{
				right = mid - 1;
			}
		}
	}
	return -1;
}
int main()
{
	setlocale(LC_ALL, "Rus");
	const int n = 5;
	int key;
	int arr[n];
	cout << "Введите элементы массива в порядке возрастания: ";
	for (int i = 0; i < n; i++)
	{
		cin >> arr[i];
	}
	cout << "Введите элемент, который нужно найти: ";
	cin >> key;
	int index = binarySearchRec(arr, n, key);
	if (index == -1)
	{ 
		cout << "Элемент " << key << " не найден" << endl;
	}
	else
	{
		cout << "Элемент " << key << " найден под номером " << index+1 << endl;
	}
	return 0;
}