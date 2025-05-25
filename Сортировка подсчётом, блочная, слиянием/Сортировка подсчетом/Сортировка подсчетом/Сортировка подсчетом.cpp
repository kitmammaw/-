#include <iostream>
#include <clocale>
using namespace std;

const int MAX_BUCKET_SIZE = 10; // Максимальный размер каждой корзины
const int NUM_BUCKETS = 10;     // Количество корзин (0-9, 10-19, ..., 90-99)

void bucketSort(int arr[], int length) 
{
    int buckets[NUM_BUCKETS][MAX_BUCKET_SIZE];
    int bucketSizes[NUM_BUCKETS] = { 0 };

    // Шаг 1: Распределение по корзинам
    for (int i = 0; i < length; i++) 
    {
        int bucketIndex = arr[i] / 10;

        // Проверка на переполнение корзины
        if (bucketSizes[bucketIndex] >= MAX_BUCKET_SIZE) 
        {
            cout << "Ошибка: Корзина " << bucketIndex << " переполнена. Увеличьте MAX_BUCKET_SIZE." << endl;
            return; // Или можно выбрать другую стратегию, например, пропустить элемент
        }

        buckets[bucketIndex][bucketSizes[bucketIndex]] = arr[i];
        bucketSizes[bucketIndex]++;
    }

    // Шаг 2: Сортировка каждой корзины (вставками)
    for (int i = 0; i < NUM_BUCKETS; i++) 
    {
        for (int j = 1; j < bucketSizes[i]; j++) 
        {
            int temp = buckets[i][j];
            int k = j - 1;
            while (k >= 0 && buckets[i][k] > temp) 
            {
                buckets[i][k + 1] = buckets[i][k];
                k--;
            }
            buckets[i][k + 1] = temp;
        }
    }

    // Шаг 3: Слияние корзин обратно в основной массив и вывод массива на каждом шаге
    cout << "Массив после слияния каждой корзины:" << endl;
    int index = 0;
    for (int i = 0; i < NUM_BUCKETS; i++) 
    {
        for (int j = 0; j < bucketSizes[i]; j++) 
        {
            arr[index++] = buckets[i][j];
        }

        // Вывод массива после слияния каждой корзины
        for (int k = 0; k < length; k++) 
        {
            cout << arr[k] << " ";
        }
        cout << endl;
    }
}

int main() 
{
    setlocale(LC_ALL, "rus");
    int n;
    cout << "Введите размер массива: ";
    cin >> n;

    int* arr = new int[n]; // Динамическое выделение памяти

    cout << "Введите элементы массива (0-99): " << endl;
    for (int i = 0; i < n; i++) 
    {
        cout << "arr[" << i << "] = ";
        cin >> arr[i];
        if (arr[i] < 0 || arr[i] > 99) 
        {
            cout << "Ошибка: Элементы массива должны быть в диапазоне 0-99." << endl;
            delete[] arr;
            return 1;
        }
    }

    cout << "Исходный массив:" << endl;
    for (int i = 0; i < n; i++) 
    {
        cout << arr[i] << " ";
    }
    cout << endl;

    bucketSort(arr, n);

    cout << "\nОтсортированный массив:" << endl;
    for (int i = 0; i < n; i++) 
    {
        cout << arr[i] << " ";
    }
    cout << endl;

    delete[] arr; // Освобождаем выделенную память
    return 0;
}