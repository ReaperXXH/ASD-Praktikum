// Bab				: BFS dan DFS
// Nama			    : Davin Kenaz Widiananda Tappo
// NIM				: 235150301111026
// Kelas            : Teknik Komputer B

#include <iostream>

using namespace std;

struct Node
{
    int key;
    Node* left;
    Node* right;
};

// Membuat node baru
Node* newNode(int item)
{
    Node* temp = new Node;
    temp->key = item;
    temp->left = temp->right = nullptr;
    return temp;
}

// Menampilkan node secar inorder atau dari paling kecil
void inorder(Node* root)
{
    if (root != nullptr)
    {
        inorder(root->left);
        cout << root->key << " ";
        inorder(root->right);
    }
}

// Menyisipkan node baru
Node* insert(Node* node, int key)
{
    if (node == nullptr)
        return newNode(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);

    return node;
}

// Mencari node dengan nilai terkecil pada subtree
Node* minValueNode(Node* node)
{
    Node* current = node;
    while (current && current->left != nullptr)
        current = current->left;
    return current;
}

// Menghapus node
Node* remove(Node* root, int key)
{
    if (root == nullptr)
        return root;

    if (key < root->key)
        root->left = remove(root->left, key);
    else if (key > root->key)
        root->right = remove(root->right, key);
    else
    {
        // Untuk node tidak punya anak atau hanya 1 anak
        if (root->left == nullptr)
        {
            Node* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == nullptr)
        {
            Node* temp = root->left;
            delete root;
            return temp;
        }

        // Untuk Node dengan 2 anak
        Node* temp = minValueNode(root->right);
        root->key = temp->key;
        root->right = remove(root->right, temp->key);
    }
    return root;
}

// Menampilkan bentuk tree
void printTree(Node* root, int level = 0)
{
    if (root == nullptr)
        return;

    printTree(root->right, level + 1);

    for (int i = 0; i < level; i++)
        cout << "    ";

    cout << root->key << endl;

    printTree(root->left, level + 1);
}

// Menghapus node terkecil pada subtree kanan root
Node* deleteKanan(Node* root)
{
    if (root == nullptr)
        return root;

    if (root->right != nullptr)
    {
        Node* temp = root->right;
        if (temp->left == nullptr)
        {
            root->right = temp->right;
            delete temp;
        }
        else
        {
            while (temp->left->left != nullptr)
                temp = temp->left;
            Node* smallest = temp->left;
            temp->left = smallest->right;
            delete smallest;
        }
    }
    return root;
}

// Menampilkan node dari paling besar
void tranverse(Node* root)
{
    if (root != nullptr)
    {
        tranverse(root->right);
        cout << root->key << " ";
        tranverse(root->left);
    }
}

int main()
{
    Node* root = nullptr;
    root = insert(root, 50);
    insert(root, 30);
    insert(root, 20);
    insert(root, 40);
    insert(root, 70);
    insert(root, 60);
    insert(root, 80);
    cout << "\nOutput BST : \n";
    inorder(root);

    remove(root, 40);
    cout << "\nOutput setelah 40 dihapus : \n";
    inorder(root);

    insert(root, 2);
    insert(root, 7);
    insert(root, 1);
    insert(root, 89);
    insert(root, 5);
    insert(root, 23);
    insert(root, 1);
    cout << "\nOutput setelah data baru dimasukan : \n";
    inorder(root);

    remove(root, 89);
    remove(root, 5);
    remove(root, 23);

    cout << "\nOutput setelah penghapusan : \n";
    inorder(root);

    cout << "\nOutput setelah nilai terkecil pada subtree kanan dihapus : \n";
    deleteKanan(root);
    inorder(root);

    cout << "\nPengurutan dari paling besar : \n";
    tranverse(root);

    cout << "\nBST : \n\n";
    printTree(root);

    return 0;
}