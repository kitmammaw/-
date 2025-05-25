#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

// Функция для вывода массива
void printArray(int arr[], int size)
{
    cout << "Массив: ";
    for (int i = 0; i < size; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void createArray(int arr[], int size)
{
    for (int i = 0; i < size; ++i)
    {
        cout << "Введите " << i + 1 << " элемент: ";
        cin >> arr[i];
    }
}

void merge(int arr[], int leftPart, int midPart, int rightPart)
{ //сливаем
    int leftRange = midPart - leftPart + 1;
    int rightRange = rightPart - midPart;

    int* leftArr = new int[leftRange];
    int* rightArr = new int[rightRange];

    for (int i = 0; i < leftRange; i++) { leftArr[i] = arr[leftPart + i]; }
    for (int i = 0; i < rightRange; i++) { rightArr[i] = arr[midPart + 1 + i]; }

    int leftIndex = 0;
    int rightIndex = 0;
    int mergeIndex = leftPart;

    while (leftIndex < leftRange && rightIndex < rightRange)
    {
        arr[mergeIndex++] = (leftArr[leftIndex] <= rightArr[rightIndex]) ? leftArr[leftIndex++] : rightArr[rightIndex++];
    }

    while (leftIndex < leftRange)  arr[mergeIndex++] = leftArr[leftIndex++];
    while (rightIndex < rightRange) arr[mergeIndex++] = rightArr[rightIndex++];

    delete[] leftArr;
    delete[] rightArr;
    printArray(arr, 5); // Вывод массива после слияния
}

void mergeSort(int arr[], int start, int end)
{ //делим
    if (start >= end) { return; }

    int mid = start + (end - start) / 2;

    mergeSort(arr, start, mid);
    mergeSort(arr, mid + 1, end);
    merge(arr, start, mid, end);
}

int main()
{
    setlocale(LC_ALL, "ru");
    int const n = 5; // Уменьшил размер массива для более наглядного вывода
    int arr[n];
    createArray(arr, n);
    printArray(arr, n);

    cout << "Сортировка подсчетом" << endl;
    mergeSort(arr, 0, n - 1);
    cout << "Сортировка завершена." << endl;

    printArray(arr, n);
    return 0;
}