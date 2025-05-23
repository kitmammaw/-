#include "node.h"
#include <algorithm>

Node::Node(char d) : data(d), left(nullptr), right(nullptr) {}

Node* Node::buildPerfectTree(const std::vector<char>& values, int start, int end) {
    if (start > end) return nullptr;
    int mid = (start + end) / 2;
    Node* node = new Node(values[mid]);
    node->left = buildPerfectTree(values, start, mid - 1);
    node->right = buildPerfectTree(values, mid + 1, end);
    return node;
}

Node* Node::buildBSTFromSorted(const std::vector<char>& values, int start, int end) {
    return buildPerfectTree(values, start, end); // работает, если вход отсортирован
}

Node* Node::insert(Node* root, char value) {
    if (!root) return new Node(value);
    if (value == root->data) return root; // не вставляем дубликаты
    if (value < root->data)
        root->left = insert(root->left, value);
    else
        root->right = insert(root->right, value);
    return root;
}

Node* Node::findMin(Node* node) {
    while (node && node->left) node = node->left;
    return node;
}

Node* Node::remove(Node* root, char value) {
    if (!root) return nullptr;
    if (value < root->data)
        root->left = remove(root->left, value);
    else if (value > root->data)
        root->right = remove(root->right, value);
    else {
        if (!root->left) {
            Node* temp = root->right;
            delete root;
            return temp;
        } else if (!root->right) {
            Node* temp = root->left;
            delete root;
            return temp;
        } else {
            Node* temp = findMin(root->right);
            root->data = temp->data;
            root->right = remove(root->right, temp->data);
        }
    }
    return root;
}

Node* Node::search(Node* root, char value) {
    if (!root || root->data == value) return root;
    if (value < root->data)
        return search(root->left, value);
    else
        return search(root->right, value);
}

int Node::height(Node* root) {
    if (!root) return 0;
    return 1 + std::max(height(root->left), height(root->right));
}

void Node::preorder(Node* root, QString& out) {
    if (!root) return;
    out += root->data;
    out += ' ';
    preorder(root->left, out);
    preorder(root->right, out);
}

void Node::inorder(Node* root, QString& out) {
    if (!root) return;
    inorder(root->left, out);
    out += root->data;
    out += ' ';
    inorder(root->right, out);
}

void Node::postorder(Node* root, QString& out) {
    if (!root) return;
    postorder(root->left, out);
    postorder(root->right, out);
    out += root->data;
    out += ' ';
}

void Node::gatherInorder(Node* root, std::vector<char>& values) {
    if (!root) return;
    gatherInorder(root->left, values);
    values.push_back(root->data);
    gatherInorder(root->right, values);
}

void Node::balanceTree(Node*& root) {
    std::vector<char> values;
    gatherInorder(root, values);
    std::sort(values.begin(), values.end()); // сортировка обязательна
    delete root;
    root = buildBSTFromSorted(values, 0, values.size() - 1);
}
