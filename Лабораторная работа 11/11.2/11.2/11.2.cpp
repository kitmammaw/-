#include <iostream>
#include <clocale> 
#include <fstream>
#include <string>
using namespace std;

struct Node {
    string key;
    Node* prev;
    Node* next;
};

Node* createList() {
    return nullptr;
}

void addElement(Node*& head, const string& key) {
    Node* newNode = new Node{ key, nullptr, head };
    if (head != nullptr) {
        head->prev = newNode;
    }
    head = newNode;
}

void deleteElement(Node*& head, const string& key) {
    if (head == nullptr) {
        cout << "Список пустой, удаление невозможно." << endl;
        return;
    }

    Node* temp = head;
    while (temp != nullptr && temp->key != key) {
        temp = temp->next;
    }

    if (temp == nullptr) {
        cout << "Элемент с таким значением не найден." << endl;
        return;
    }

    if (temp->prev != nullptr) {
        temp->prev->next = temp->next;
    }
    else {
        head = temp->next;
    }

    if (temp->next != nullptr) {
        temp->next->prev = temp->prev;
    }

    delete temp;
    cout << "Элемент \"" << key << "\" удален." << endl;
}

void printList(Node* head) {
    if (head == nullptr) {
        cout << "Список пустой." << endl;
        return;
    }

    Node* temp = head;
    while (temp != nullptr) {
        cout << temp->key << " ";
        temp = temp->next;
    }
    cout << endl;
}

void writeListToFile(Node* head, const string& filename) {
    ofstream outFile(filename);

    Node* temp = head;
    while (temp != nullptr) {
        outFile << temp->key << endl;
        temp = temp->next;
    }

    outFile.close();
    cout << "Список записан в файл \"" << filename << "\"." << endl;
}

void destroyList(Node*& head) {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    cout << "Список уничтожен." << endl;
}

Node* restoreListFromFile(const string& filename) {
    ifstream inFile(filename);
    if (!inFile) {
        cerr << "Ошибка открытия файла для чтения!" << endl;
        return nullptr;
    }

    Node* head = nullptr;
    string key;
    while (getline(inFile, key)) {
        addElement(head, key);
    }

    inFile.close();
    cout << "Список восстановлен из файла \"" << filename << "\"." << endl;
    return head;
}

int main() {
    setlocale(LC_ALL, "Rus");
    system("chcp 1251");
    system("cls");

    Node* head = createList();
    string filename = "list.txt";
    int n;
    string key;

    cout << "Введите количество элементов: ";
    cin >> n;
    for (int i = 0; i < n; i++) {
        cout << "Введите элемент " << i + 1 << ": ";
        cin >> key;
        addElement(head, key);
    }

    cout << "\nСписок после добавления элементов:" << endl;
    printList(head);

    cout << "\nВведите элемент для удаления: ";
    cin >> key;
    deleteElement(head, key);

    cout << "\nСписок после удаления элемента:" << endl;
    printList(head);

    writeListToFile(head, filename);

    destroyList(head);

    cout << "\nСписок после уничтожения:" << endl;
    printList(head);

    head = restoreListFromFile(filename);

    cout << "\nСписок после восстановления из файла:" << endl;
    printList(head);

    destroyList(head);

    return 0;
}
