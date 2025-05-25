#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

// Функция для вывода массива (для пошагового вывода)
void printArray(int arr[], int start, int end) {
    for (int i = start; i <= end; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void merge(int arr[], int leftPart, int midPart, int rightPart) { //сливаем
    int leftRange = midPart - leftPart + 1;
    int rightRange = rightPart - midPart;

    int* leftArr = new int[leftRange];
    int* rightArr = new int[rightRange];

    for (int i = 0; i < leftRange; i++) { leftArr[i] = arr[leftPart + i]; }
    for (int i = 0; i < rightRange; i++) { rightArr[i] = arr[midPart + 1 + i]; }

    int leftIndex = 0;
    int rightIndex = 0;
    int mergeIndex = leftPart;

    while (leftIndex < leftRange && rightIndex < rightRange) {
        if (leftArr[leftIndex] <= rightArr[rightIndex]) {
            arr[mergeIndex] = leftArr[leftIndex];
            leftIndex++;
        }
        else {
            arr[mergeIndex] = rightArr[rightIndex];
            rightIndex++;
        }
        mergeIndex++;
    }

    while (leftIndex < leftRange) {
        arr[mergeIndex] = leftArr[leftIndex];
        leftIndex++;
        mergeIndex++;
    }
    while (rightIndex < rightRange) {
        arr[mergeIndex] = rightArr[rightIndex];
        rightIndex++;
        mergeIndex++;
    }

    // Вывод массива после слияния
    cout << "Массив после слияния: ";
    printArray(arr, 0, rightPart);  // Выводим весь массив

    delete[] leftArr;
    delete[] rightArr;
}

void mergeSort(int arr[], int start, int end) { //делим
    if (start >= end) {
        return;
    }

    int mid = start + (end - start) / 2;
    mergeSort(arr, start, mid);
    mergeSort(arr, mid + 1, end);
    merge(arr, start, mid, end);
}

int main()
{
    setlocale(LC_ALL, "ru");
    int n;

    cout << "Введите размер массива: ";
    cin >> n;

    int* arr = new int[n];

    cout << "Введите элементы массива: " << endl;
    for (int i = 0; i < n; i++) {
        cout << "arr[" << i << "] = ";
        cin >> arr[i];
    }

    cout << "Массив:" << endl;
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    cout << "Oтсортированный Массив:" << endl;
    mergeSort(arr, 0, n - 1);

    cout << "Отсортированный массив: ";
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl; // Добавил перенос строки для лучшей читаемости

    delete[] arr; // Освобождаем выделенную память

    return 0;
}

