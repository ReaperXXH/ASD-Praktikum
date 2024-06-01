#include <iostream>
#include <time.h> // time

using namespace std;

struct Node {
    int data;
    Node *anakKiri;
    Node *anakKanan;
    Node(int);
};

struct Tree {
    Node *root;
    Tree();
    void sisipDtNode(int);
    void preorderTraversal();
    void inorderTraversal();
    void postorderTraversal();
    int Node_Counter();
    int leaf_Counter();
    int height_counter();
    private:
    void sisipDt(Node*, int);
    void preorder(Node*);
    void inorder(Node*);
    void postorder(Node*);
    int Node_Count(Node *);
    int leaf_Count(Node *);
    int height_Count(Node *);
};

Node::Node(int dt) {
    data = dt;
    anakKiri = anakKanan = nullptr;
}

Tree::Tree() {
    root = nullptr;
}

void Tree::sisipDtNode(int dtSisip) {
    if (root == nullptr)
    root = new Node(dtSisip);
    else
    sisipDt(root, dtSisip);
}

void Tree::preorderTraversal() {
    preorder(root);
}

void Tree::inorderTraversal() {
    inorder(root);
}

void Tree::postorderTraversal() {
    postorder(root);
}

int Tree::Node_Counter(){
    Node_Count(root);
}

int Tree::leaf_Counter(){
    leaf_Count(root);
}

int Tree::height_counter(){
    height_Count(root);
}

void Tree::sisipDt(Node *node, int dtSisip) {
    if (dtSisip < node->data) {
    if (node->anakKiri == nullptr)
    node->anakKiri = new Node(dtSisip);
    else
    sisipDt(node->anakKiri, dtSisip);
    }
    else if (dtSisip > node->data) {
    if (node->anakKanan == nullptr)
    node->anakKanan = new Node(dtSisip);
    else
    sisipDt(node->anakKanan, dtSisip);
    }
}
void Tree::preorder(Node* node) {
    if (node == nullptr) return;
    cout << node->data << ", ";
    preorder(node->anakKiri);
    preorder(node->anakKanan);
}
void Tree::inorder(Node* node) {
    if (node == nullptr) return;
    inorder(node->anakKiri);
    cout << node->data << ", ";
    inorder(node->anakKanan);
}
void Tree::postorder(Node* node) {
    if (node == nullptr) return;
    postorder(node->anakKiri);
    postorder(node->anakKanan);
    cout << node->data << ", ";
}

int Tree::Node_Count(Node * TreeNode){
    if (TreeNode== nullptr) return 0;
    return 1 + Node_Count(TreeNode->anakKiri) + Node_Count(TreeNode->anakKanan);
}

int Tree::leaf_Count(Node * TreeNode){
    if (TreeNode == nullptr) return 0;
    if (TreeNode->anakKanan == nullptr && TreeNode->anakKiri == nullptr){
        return 1;
    }
     return leaf_Count(TreeNode->anakKiri) + leaf_Count(TreeNode->anakKanan);
}

int Tree::height_Count(Node *TreeNode){
    //jika tree kosong
    if (TreeNode == nullptr) 
    return -1; //-1 artinya tree kosong (tidak punya height)
    int Right_Height = height_Count(TreeNode->anakKanan); // menelusuri banyak anak kanan
    int Left_Height = height_Count(TreeNode ->anakKiri); // menelusuri banyak anak kiri
     if (Right_Height > Left_Height)
        return 1 + Right_Height ;
    else 
        return 1+ Left_Height;
}
int main() {
    Tree *tree = new Tree();
    int nilai;
    cout << "Sisip nilai data berikut: " << endl;
    // sisip data 10 bilangan acak dari 0-99 ke dalam tree
    srand(time(nullptr));
    for (int i = 0; i < 10; i++) {
    nilai = rand() % 100;
    cout << nilai << " ";
    tree->sisipDtNode(nilai);
    }
    cout << "\n\nPreorder Traversal" << endl;
    tree->preorderTraversal();
    cout << "\n\nInorder Traversal" << endl;
    tree->inorderTraversal();
    cout << "\n\nPostorder Traversal" << endl;
    tree->postorderTraversal();
    cout << endl << endl << "Jumlah node dalam BST adalah :" <<tree->Node_Counter();
    cout << endl << endl << "Jumlah node leaf dalam BST adalah :" <<tree->leaf_Counter();
    cout << endl << endl << "Tinggi BST adalah :" <<tree->height_counter();
}