#include <iostream>
#include <clocale>
using namespace std;

// Функция для вывода массива
void printArray(int arr[], int size) 
{
    for (int i = 0; i < size; i++)
    cout << arr[i] << " ";
    cout << endl;
}

// Функция сортировки Шелла с минимальным выводом
void shellSort(int arr[], int n) 
{
    for (int h = n / 2; h > 0; h /= 2) 
    {
        for (int i = h; i < n; i++) 
        {
            int tmp = arr[i];
            int j;
            for (j = i; j >= h && arr[j - h] > tmp; j -= h) 
            {
                arr[j] = arr[j - h];
            }
            arr[j] = tmp;
        }
        cout << "Массив: ";
        printArray(arr, n);
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    int n;

    cout << "Введите размер массива: ";
    cin >> n;

    int* arr = new int[n]; // Динамическое выделение памяти

    cout << "Введите элементы массива: ";
    for (int i = 0; i < n; i++) 
    {
        cin >> arr[i];
    }

    cout << "Исходный массив: ";
    printArray(arr, n);
    cout << endl;

    shellSort(arr, n);

    cout << "Отсортированный массив: ";
    printArray(arr, n);

    delete[] arr; // Освобождение памяти
    return 0;
}
