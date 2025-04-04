#include <iostream>
#include <clocale>
using namespace std;

int binary_search(int arr[], const int n, int key) 
{
    int left = 0, right = n - 1;

    while (left <= right) 
    {
        int mid = left + (((key - arr[left]) * (right - left)) / (arr[right] - arr[left]));

        if (arr[mid] == key) 
        {
            return mid; // возвращаем индекс найденного элемента
        }
        else 
        {
            if (arr[mid] < key) 
            {
                left = mid + 1; // ищем в правой половине массива
            }
            else 
            {
                right = mid - 1; // ищем в левой половине массива
            }
        }
    }
    return -1; // возвращаем -1, если элемент не найден
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
    cout << "Введите элемент для поиска: ";
    cin >> key;
    int index = binary_search(arr, n, key);
    if (index == -1) 
    {
        cout << "Элемент " << key << " не найден\n";
    }
    else 
    {
        cout << "Элемент " << key << "  найден под номером " << index + 1 << endl;
    }
    return 0;
}

