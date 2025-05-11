#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Простая структура Node для очереди (FIFO - Первый пришел, первый ушел)
struct Node
{
    string data;
    Node* next;
};

// Функция для создания очереди (возвращает указатели на начало и конец, оба nullptr)
pair<Node*, Node*> createQueue()
{
    return { nullptr, nullptr }; // Указатели на начало и конец очереди
}

// Функция для добавления элемента в очередь (постановка в очередь)
void addElement(pair<Node*, Node*>& queuePointers, const string& key)
{
    Node* newNode = new Node{ key, nullptr };

    if (queuePointers.first == nullptr) // Очередь пуста
    {
        queuePointers.first = newNode;
        queuePointers.second = newNode;
    }
    else
    {
        queuePointers.second->next = newNode; // Добавить в конец
        queuePointers.second = newNode;       // Обновить указатель на конец
    }
}

// Функция для удаления элемента из очереди (по значению - требует перебора)
void deleteElement(pair<Node*, Node*>& queuePointers, const string& key)
{
    Node* head = queuePointers.first;
    Node* tail = queuePointers.second;

    if (head == nullptr)
    {
        cout << "Очередь пустая, удаление невозможно." << endl;
        return;
    }

    Node* current = head;
    Node* previous = nullptr;
    bool found = false;

    while (current != nullptr)
    {
        if (current->data == key && !found)
        {  // Нашли элемент (удаляем только первый)
            found = true;

            if (previous == nullptr)
            { // Удаляем элемент в начале очереди (head)
                head = current->next;
                queuePointers.first = head; // Обновляем начало очереди

                if (head == nullptr)
                { // Очередь стала пустой
                    queuePointers.second = nullptr;
                }

            }
            else
            {
                previous->next = current->next;

                if (current == tail)
                {
                    queuePointers.second = previous; // Настраиваем tail при удалении последнего
                }
            }
            Node* temp = current;
            current = current->next;
            delete temp;
            cout << "Элемент \"" << key << "\" удален." << endl;

        }
        else
        {
            previous = current;
            current = current->next;
        }
    }

    if (!found)
    {
        cout << "Элемент с таким значением не найден." << endl;
    }
    queuePointers.first = head;
    queuePointers.second = tail;

}

// Функция для печати очереди (перебирает, не изменяет)
void printQueue(pair<Node*, Node*> queuePointers)
{
    Node* head = queuePointers.first;

    if (head == nullptr)
    {
        cout << "Очередь пустая." << endl;
        return;
    }

    Node* current = head;
    while (current != nullptr)
    {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

// Функция для записи очереди в файл (перебирает)
void writeQueueToFile(pair<Node*, Node*> queuePointers, const string& filename)
{
    Node* head = queuePointers.first;
    ofstream outFile(filename);

    if (!outFile.is_open())
    {
        cerr << "Ошибка открытия файла для записи!" << endl;
        return;
    }

    Node* current = head;
    while (current != nullptr)
    {
        outFile << current->data << endl;
        current = current->next;
    }

    outFile.close();
    cout << "Очередь записана в файл \"" << filename << "\"." << endl;
}

// Функция для уничтожения очереди (освобождает память)
void destroyQueue(pair<Node*, Node*>& queuePointers)
{
    Node* head = queuePointers.first;

    while (head != nullptr)
    {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    queuePointers.first = nullptr; // Обнуляем указатели
    queuePointers.second = nullptr;
    cout << "Очередь уничтожена." << endl;
}

// Функция для восстановления очереди из файла (считывает элементы)
pair<Node*, Node*> restoreQueueFromFile(const string& filename)
{
    ifstream inFile(filename);
    if (!inFile)
    {
        cerr << "Ошибка открытия файла для чтения!" << endl;
        return createQueue();  // Возвращает пустую очередь.
    }

    pair<Node*, Node*> newQueue = createQueue(); // Начинаем с пустой очереди.
    string key;
    while (getline(inFile, key))
    {
        addElement(newQueue, key); // Добавляет элементы в конец.
    }

    inFile.close();
    cout << "Очередь восстановлена из файла " << filename << endl;
    return newQueue;
}

int main()
{
    setlocale(LC_ALL, "Rus");
    system("chcp 1251");
    system("cls");

    pair<Node*, Node*> q = createQueue(); // Очередь создается как пара указателей.
    string filename = "queue.txt";
    int n;
    string key;

    cout << "Введите количество элементов: ";
    cin >> n;
    cin.ignore();

    for (int i = 0; i < n; i++)
    {
        cout << "Введите элемент " << i + 1 << ": ";
        getline(cin, key);
        addElement(q, key);
    }

    cout << "Очередь после добавления элементов:" << endl;
    printQueue(q);

    cout << "Введите элемент для удаления: ";
    getline(cin, key);
    deleteElement(q, key);

    cout << "Очередь после удаления элемента:" << endl;
    printQueue(q);

    writeQueueToFile(q, filename);

    destroyQueue(q);

    cout << "Очередь после уничтожения:" << endl;
    printQueue(q);  // Должна быть пустой

    q = restoreQueueFromFile(filename);

    cout << "Очередь после восстановления из файла:" << endl;
    printQueue(q);

    destroyQueue(q);

    return 0;
}

