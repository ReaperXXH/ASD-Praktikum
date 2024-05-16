#include <iostream>
using namespace std;

const int MAX_SIZE = 40;

struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;
};

TreeNode* createNode(int data) {
    TreeNode* newNode = new TreeNode();
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

TreeNode* insertNode(TreeNode* root, int data) {
    if (root == NULL) {
        return createNode(data);
    }

    if (data < root->data) {
        root->left = insertNode(root->left, data);
    } else if (data > root->data) {
        root->right = insertNode(root->right, data);
    }

    return root;
}

void inorderTraversal(TreeNode* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        cout << root->data << " ";
        inorderTraversal(root->right);
    }
}

int main() {
    int numNodes, nodeValue;
    TreeNode* root = NULL;

    cout << "Masukkan jumlah node BST: ";
    cin >> numNodes;

    cout << "Masukkan nilai node BST: ";
    for (int i = 0; i < numNodes; ++i) {
        cin >> nodeValue;
        if (nodeValue <= MAX_SIZE) {
            root = insertNode(root, nodeValue);
        } else {
            cout << "Node " << nodeValue << " tidak dimasukkan karena melebihi indeks maksimum." << endl;
        }
    }

 
    cout << "Isi BST secara inorder: ";
    inorderTraversal(root);
    cout << endl;

    return 0;
}
