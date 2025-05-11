#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Node 
{
    string key;
    Node* next;
};

// Функция для создания стека
Node* createStack() 
{
    return nullptr; // Возвращаем пустой стек.
}

// Функция для добавления элемента в стек
void addElement(Node*& head, const string& key) 
{
    Node* newNode = new Node{ key, head };
    head = newNode; // Делаем новый элемент вершиной стека.
}

// Функция для удаления элемента из стека (по значению)
void deleteElement(Node*& head, const string& key) 
{
    if (head == nullptr) 
    
    {
        cout << "Стек пустой, удаление невозможно." << endl;
        return;
    }

    Node* current = head;
    Node* previous = nullptr;

    while (current != nullptr && current->key != key) 
    {
        previous = current;
        current = current->next;
    }

    if (current == nullptr) 
    {
        cout << "Элемент с таким значением не найден" << endl;
        return;
    }

    if (previous == nullptr) 
    {
        // Удаляем элемент с вершины стека
        head = current->next;
    }
    else 
    {
        previous->next = current->next;
    }

    delete current;
    cout << "Элемент " << key << " удален" << endl;
}

// Функция для печати стека
void printStack(Node* head) 
{
    if (head == nullptr) 
    {
        cout << "Стек пустой" << endl;
        return;
    }

    Node* current = head;
    while (current != nullptr) 
    {
        cout << current->key << " ";
        current = current->next;
    }
    cout << endl;
}

// Функция для записи стека в файл
void writeStackToFile(Node* head, const string& filename) {
    ofstream outFile(filename);

    if (!outFile.is_open()) {
        cerr << "Ошибка открытия файла для записи!" << endl;
        return;
    }

    Node* current = head;
    
    string* keys = new string[1000];
    int count = 0;
    while (current != nullptr) 
    {
        keys[count++] = current->key;
        current = current->next;
    }
    for (int i = count - 1; i >= 0; i--) 
    {
        outFile << keys[i] << endl;
    }
    delete[] keys;
    outFile.close();
    cout << "Стек записан в файл " << filename << endl;
}

// Функция для уничтожения стека
void destroyStack(Node*& head) 
{
    while (head != nullptr) 
    {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    cout << "Стек уничтожен" << endl;
}

// Функция для восстановления стека из файла
Node* restoreStackFromFile(const string& filename) 
{
    ifstream inFile(filename);
    if (!inFile) 
    {
        cerr << "Ошибка открытия файла для чтения!" << endl;
        return nullptr; // Возвращаем пустой стек при ошибке.
    }

    Node* head = nullptr;
    string key;

    string* keys = new string[1000];
    int count = 0;
    while (getline(inFile, key)) 
    {
        keys[count++] = key;
    }
    inFile.close();

    for (int i = count - 1; i >= 0; i--) 
    {
        addElement(head, keys[i]);
    }
    delete[] keys;
    cout << "Стек восстановлен из файла " << filename << endl;
    return head;
}

int main() 
{
    setlocale(LC_ALL, "Rus"); 
    system("chcp 1251");     
    system("cls");

    Node* s = createStack();
    string filename = "stack.txt";
    int n;
    string key;

    cout << "Введите количество элементов: ";
    cin >> n;
    cin.ignore(); // Потребляем символ новой строки после чтения n.

    for (int i = 0; i < n; i++) 
    {
        cout << "Введите элемент " << i + 1 << ": ";
        getline(cin, key);
        addElement(s, key);
    }

    cout << "Стек после добавления элементов: " << endl;
    printStack(s);

    cout << "Введите элемент для удаления: ";
    getline(cin, key);
    deleteElement(s, key);

    cout << "Стек после удаления элемента: " << endl;
    printStack(s);

    writeStackToFile(s, filename);

    destroyStack(s);

    cout << "Стек после уничтожения: " << endl;
    printStack(s);  // Должен быть пустой

    s = restoreStackFromFile(filename);

    cout << "Стек после восстановления из файла: " << endl;
    printStack(s);

    destroyStack(s);

    return 0;
}
