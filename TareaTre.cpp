#include <iostream>
using namespace std;

template <typename T>
class AVLTree {
private:
    struct Node {
        T data;
        Node* left;
        Node* right;
        int height;
        Node(T val) : data(val), left(nullptr), right(nullptr), height(1) {}
    };

    Node* root;

    int height(Node* n) {
        return n ? n->height : 0;
    }

    int balanceFactor(Node* n) {
        return n ? height(n->left) - height(n->right) : 0;
    }

    void updateHeight(Node* n) {
        if (n) {
            n->height = 1 + max(height(n->left), height(n->right));
        }
    }

    Node* rotateRight(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;
        x->right = y;
        y->left = T2;
        updateHeight(y);
        updateHeight(x);
        return x;
    }

    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;
        y->left = x;
        x->right = T2;
        updateHeight(x);
        updateHeight(y);
        return y;
    }

    Node* balance(Node* n) {
        updateHeight(n);
        int bf = balanceFactor(n);
        if (bf > 1) {
            if (balanceFactor(n->left) < 0) {
                n->left = rotateLeft(n->left);
            }
            return rotateRight(n);
        }
        if (bf < -1) {
            if (balanceFactor(n->right) > 0) {
                n->right = rotateRight(n->right);
            }
            return rotateLeft(n);
        }
        return n;
    }

    Node* insert(Node* node, T key) {
        if (!node) return new Node(key);
        if (key < node->data) {
            node->left = insert(node->left, key);
        } else if (key > node->data) {
            node->right = insert(node->right, key);
        } else {
            return node;
        }
        return balance(node);
    }

    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    Node* deleteNode(Node* root, T key) {
        if (!root) return root;
        if (key < root->data) {
            root->left = deleteNode(root->left, key);
        } else if (key > root->data) {
            root->right = deleteNode(root->right, key);
        } else {
            if (!root->left || !root->right) {
                Node* temp = root->left ? root->left : root->right;
                if (!temp) {
                    temp = root;
                    root = nullptr;
                } else {
                    *root = *temp;
                }
                delete temp;
            } else {
                Node* temp = minValueNode(root->right);
                root->data = temp->data;
                root->right = deleteNode(root->right, temp->data);
            }
        }
        if (!root) return root;
        return balance(root);
    }

    void inOrder(Node* root) {
        if (root) {
            inOrder(root->left);
            cout << root->data << " ";
            inOrder(root->right);
        }
    }

    void printTree(Node* root, int space) {
        if (root == nullptr)
            return;

        space += 10;

        printTree(root->right, space);

        cout << endl;
        for (int i = 10; i < space; i++)
            cout << " ";
        cout << root->data << "\n";

        printTree(root->left, space);
    }

public:
    AVLTree() : root(nullptr) {}

    void insert(T key) {
        root = insert(root, key);
    }

    void deleteNode(T key) {
        root = deleteNode(root, key);
    }

    void inOrder() {
        inOrder(root);
        cout << endl;
    }

    void printTree() {
        printTree(root, 0);
    }
};

int main() {
    AVLTree<int> tree;
    int choice, value;

    do {
        cout << "1. Insertar nodo" << endl;
        cout << "2. Eliminar nodo" << endl;
        cout << "3. Mostrar recorrido en orden" << endl;
        cout << "4. Mostrar arbol" << endl;
        cout << "5. Salir" << endl;
        cout << "Ingrese su eleccion: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Ingrese el valor a insertar: ";
                cin >> value;
                tree.insert(value);
                break;
            case 2:
                cout << "Ingrese el valor a eliminar: ";
                cin >> value;
                tree.deleteNode(value);
                break;
            case 3:
                cout << "Recorrido en orden del arbol AVL: ";
                tree.inOrder();
                break;
            case 4:
                cout << "Visualizacion del arbol AVL: " << endl;
                tree.printTree();
                break;
            case 5:
                cout << "Saliendo..." << endl;
                break;
            default:
                cout << "Opcion no valida. Intente de nuevo." << endl;
        }
    } while (choice != 5);

    return 0;
}