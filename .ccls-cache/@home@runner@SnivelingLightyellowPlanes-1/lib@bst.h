#include <iostream>
#include <iomanip>
#include <memory>
#include <vector>

using namespace std;

class TreeNode {
public:
    int value;
    string tag;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int val, const string& t) : value(val), tag(t), left(nullptr), right(nullptr) {}
};

using TreeNodePtr = TreeNode*;

class BST {
private:
    TreeNodePtr root;

    TreeNodePtr insert(TreeNodePtr node, int value, const string& tag);
    void inOrderTraversal(TreeNodePtr node);
    void printTree(TreeNodePtr treePtr, int level, bool isLeft);

public:
    BST() : root(nullptr) {}

    void insert(int value, const string& tag);
    void insert(const vector<pair<string, int>>& vec); // New function to insert vector of pairs
    void inOrderTraversal();
    void printTree();
};

TreeNodePtr BST::insert(TreeNodePtr node, int value, const string& tag) {
    if (node == nullptr) {
        return new TreeNode(value, tag);
    }

    if (value < node->value) {
        node->left = insert(node->left, value, tag);
    } else if (value > node->value) {
        node->right = insert(node->right, value, tag);
    }

    return node;
}

void BST::insert(int value, const string& tag) {
    root = insert(root, value, tag);
}

void BST::insert(const vector<pair<string, int>>& vec) {
    for (const auto& pair : vec) {
        insert(pair.second, pair.first);
    }
}

void BST::inOrderTraversal(TreeNodePtr node) {
    if (node == nullptr) {
        return;
    }
    inOrderTraversal(node->left);
    cout << node->value << " (" << node->tag << ") ";
    inOrderTraversal(node->right);
}

void BST::inOrderTraversal() {
    inOrderTraversal(root);
}

void BST::printTree(TreeNodePtr treePtr, int level, bool isLeft) {
    if (treePtr) {
        printTree(treePtr->right, level + 1, false);

        if (level != 0) {
            cout << setw(level * 4 - 2) << "";
            if (isLeft) {
                cout << "\\";
            } else {
                cout << "/";
            }
        }

        cout << treePtr->value << " (" << treePtr->tag << ")" << endl;

        printTree(treePtr->left, level + 1, true);
    }
}

void BST::printTree() {
    printTree(root, 0, true);
}