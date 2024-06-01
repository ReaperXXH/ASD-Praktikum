#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
using namespace std;

struct Node
{
    string value;
    vector<Node> children;

public:
    Node(string c)
    {
        value = c;
    }
    void addChild(Node n)
    {
        children.push_back(n);
        return;
    }
    void addChild(string n)
    {
        Node foo(n);
        children.push_back(foo);
    }
    string getValue()
    {
        return value;
    }
    vector<Node> getChildren()
    {
        return children;
    }
    bool isLeaf()
    {
        return children.size() == 0;
    }
    bool operator==(Node b)
    {
        return b.value == value;
    }
};

void construct(Node *r)
{
    string foo;
    cout << "Masukkan nilai anak dari " << r->getValue() << " (-1 untuk stop) : ";
    cin >> foo;
    if (foo == "-1")
        return;
    else
    {
        size_t pos = 0;
        while ((pos = foo.find(',')) != string::npos)
        {
            string token = foo.substr(0, pos);
            Node t(token);
            construct(&t);
            r->addChild(t);
            foo.erase(0, pos + 1);
        }
        if (!foo.empty()) {
            Node t(foo);
            construct(&t);
            r->addChild(t);
        }
    }
}

string breadthFirstSearch(Node root, Node goal)
{
    std::queue<Node> Q;
    std::vector<Node> children;
    string path = "";
    Q.push(root);
    while (!Q.empty())
    {
        Node t = Q.front();
        path += t.getValue() + " ";
        Q.pop();
        if (t == goal)
        {
            return path;
        }
        children = t.getChildren();
        for (int i = 0; i < children.size(); ++i)
        {
            Q.push(children[i]);
        }
    }
    return path;
}

string depthFirstSearch(Node root, Node goal)
{
    std::stack<Node> Q;
    std::vector<Node> children;
    string path = "";
    Q.push(root);
    while (!Q.empty())
    {
        Node t = Q.top();
        path += t.getValue() + " ";
        Q.pop();
        if (t == goal)
        {
            return path;
        }
        children = t.getChildren();
        std::reverse(children.begin(), children.end());
        for (int i = 0; i < children.size(); ++i)
        {
            Q.push(children[i]);
        }
    }
    return path;
}

void preOrderTraversal(Node root)
{
    if (root.getValue() != "")
    {
        cout << root.getValue() << " ";
        vector<Node> children = root.getChildren();
        for (int i = 0; i < children.size(); ++i)
        {
            preOrderTraversal(children[i]);
        }
    }
}

void postOrderTraversal(Node root)
{
    if (root.getValue() != "")
    {
        vector<Node> children = root.getChildren();
        for (int i = 0; i < children.size(); ++i)
        {
            postOrderTraversal(children[i]);
        }
        cout << root.getValue() << " ";
    }
}

int main(int argc, char **args)
{
    string r;
    cout << "Program membuat tree dan mencari menggunakan BFS dan DFS" << endl;
    cout << "Angka yang dimasukkan adalah angka dari 1 s.d. 20" << endl;
    cout << "Masukkan node root (angka atau string) : ";
    cin >> r;
    cout << "Memasukkan nilai anak, gunakan koma sebagai pemisah untuk beberapa node anak... " << endl;

    Node root(r);
    construct(&root);
    cout << endl << "Masukkan nilai node yang dicari: ";
    cin >> r;
    cout << endl;
    cout << "BFS Traversal: " << breadthFirstSearch(root, Node("")) << endl;

    cout << "BFS Search Path: " << breadthFirstSearch(root, Node(r)) << endl << endl;

    cout << "DFS Traversal: " << depthFirstSearch(root, Node("")) << endl;

    cout << "DFS Search Path: " << depthFirstSearch(root, Node(r)) << endl;

    cout << "PreOrder Traversal: " ;
    preOrderTraversal(root);

    cout << "\nPostOrder Traversal: ";
    postOrderTraversal(root);

    cout << endl << "tekan 'q' untuk keluar";
    char c;
    while (cin.get(c))
    {
        if (c == 'q')
            break;
        cout << c;
    }
    return 0;
}
