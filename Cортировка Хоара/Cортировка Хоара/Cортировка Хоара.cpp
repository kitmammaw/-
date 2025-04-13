#include <iostream>
#include <clocale>
using namespace std;

// Вспомогательная функция для вывода массива
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
        cout << arr[i] << " ";
    cout << endl;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[low];
    int num = 0;
    for (int i = low + 1; i <= high; i++) {
        if (arr[i] < pivot) { num++; }
    }
    int pos = low + num;
    swap(arr[pos], arr[low]);
    int i = low, j = high;
    while (i < pos && j > pos) {
        while (arr[i] < pivot) i++;
        while (arr[j] > pivot) j--;
        if (i < pos && j > pos) swap(arr[i++], arr[j--]);
    }
    return pos;
}

void quickSort(int arr[], int low, int high) {
    if (low >= high) return;
    int pI = partition(arr, low, high);
    cout << "Пошаговая сортировка: " ;
    printArray(arr, high + 1);
    quickSort(arr, low, pI - 1);
    quickSort(arr, pI + 1, high);
}

int main() {
    setlocale(LC_ALL, "Russian");
    int n;

    cout << "Введите размер массива: ";
    cin >> n;

    int* arr = new int[n]; // Динамическое выделение памяти

    cout << "Введите элементы массива: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    cout << "Исходный массив: ";
    printArray(arr, n);

    quickSort(arr, 0, n - 1);

    cout << "Отсортированный массив: ";
    printArray(arr, n);

    delete[] arr; // Освобождение памяти после использования
    return 0;
}


