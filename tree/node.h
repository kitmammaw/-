#ifndef NODE_H
#define NODE_H

#include <QString>
#include <vector>

class Node {
public:
    char data;
    Node* left;
    Node* right;

    Node(char d);

    static Node* buildPerfectTree(const std::vector<char>& values, int start, int end);
    static Node* insert(Node* root, char value);
    static Node* remove(Node* root, char value);
    static Node* search(Node* root, char value);
    static int height(Node* root);

    static void preorder(Node* root, QString& out);
    static void inorder(Node* root, QString& out);
    static void postorder(Node* root, QString& out);

    static void balanceTree(Node*& root);
    static void gatherInorder(Node* root, std::vector<char>& values);
    static Node* buildBSTFromSorted(const std::vector<char>& values, int start, int end);

private:
    static Node* findMin(Node* node);
};

#endif // NODE_H
