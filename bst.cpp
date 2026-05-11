#include <iostream>
using namespace std;

struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

class BST {
private:
    TreeNode* root;

    TreeNode* insertRec(TreeNode* node, int val) {
        if (!node) return new TreeNode(val);
        if (val <= node->data)
            node->left = insertRec(node->left, val);
        else
            node->right = insertRec(node->right, val);
        return node;
    }

    bool searchRec(TreeNode* node, int val) {
        if (!node) return false;
        if (node->data == val) return true;
        if (val < node->data) return searchRec(node->left, val);
        return searchRec(node->right, val);
    }

    TreeNode* findMin(TreeNode* node) {
        while (node && node->left) node = node->left;
        return node;
    }

    TreeNode* deleteRec(TreeNode* node, int val) {
        if (!node) return nullptr;
        if (val < node->data)
            node->left = deleteRec(node->left, val);
        else if (val > node->data)
            node->right = deleteRec(node->right, val);
        else {
            if (!node->left) {
                TreeNode* temp = node->right;
                delete node;
                return temp;
            }
            if (!node->right) {
                TreeNode* temp = node->left;
                delete node;
                return temp;
            }
            TreeNode* temp = findMin(node->right);
            node->data = temp->data;
            node->right = deleteRec(node->right, temp->data);
        }
        return node;
    }

    void inorderRec(TreeNode* node) {
        if (!node) return;
        inorderRec(node->left);
        cout << node->data << " ";
        inorderRec(node->right);
    }

    void preorderRec(TreeNode* node) {
        if (!node) return;
        cout << node->data << " ";
        preorderRec(node->left);
        preorderRec(node->right);
    }

    void postorderRec(TreeNode* node) {
        if (!node) return;
        postorderRec(node->left);
        postorderRec(node->right);
        cout << node->data << " ";
    }

    int heightRec(TreeNode* node) {
        if (!node) return 0;
        int left = heightRec(node->left);
        int right = heightRec(node->right);
        return 1 + (left > right ? left : right);
    }

    int countRec(TreeNode* node) {
        if (!node) return 0;
        return 1 + countRec(node->left) + countRec(node->right);
    }

    TreeNode* findParent(TreeNode* node, int val, TreeNode* parent) {
        if (!node) return nullptr;
        if (node->data == val) return parent;
        if (val < node->data) return findParent(node->left, val, node);
        return findParent(node->right, val, node);
    }

public:
    BST() : root(nullptr) {}

    void insert(int val) { root = insertRec(root, val); }
    bool search(int val) { return searchRec(root, val); }
    void remove(int val) { root = deleteRec(root, val); }

    int findMin() {
        TreeNode* node = findMin(root);
        return node ? node->data : -1;
    }

    int findMax() {
        if (!root) return -1;
        TreeNode* curr = root;
        while (curr->right) curr = curr->right;
        return curr->data;
    }

    void inorder() { inorderRec(root); cout << endl; }
    void preorder() { preorderRec(root); cout << endl; }
    void postorder() { postorderRec(root); cout << endl; }

    int height() { return heightRec(root); }
    int countNodes() { return countRec(root); }

    int findParent(int val) {
        TreeNode* parent = findParent(root, val, nullptr);
        return parent ? parent->data : -1;
    }
};

int main() {
    BST tree;
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    tree.insert(60);
    tree.insert(80);

    cout << "Inorder: "; tree.inorder();
    cout << "Preorder: "; tree.preorder();
    cout << "Postorder: "; tree.postorder();

    cout << "Min: " << tree.findMin() << ", Max: " << tree.findMax() << endl;
    cout << "Height: " << tree.height() << ", Nodes: " << tree.countNodes() << endl;

    cout << "Search 40: " << (tree.search(40) ? "Found" : "Not found") << endl;
    cout << "Parent of 40: " << tree.findParent(40) << endl;

    tree.remove(30);
    cout << "After deleting 30, inorder: "; tree.inorder();

    return 0;
}