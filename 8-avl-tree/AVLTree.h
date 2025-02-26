#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <iostream>
#include <cstdlib>
#include <iomanip>
using namespace std;

// Definición del nodo del árbol AVL
struct TreeNode {
    int key;       // clave
    int count;     // contador (para manejar duplicados)
    int balance;   // factor de balance: -1, 0, +1
    TreeNode *left, *right;

    TreeNode(int k)
            : key(k), count(1), balance(0), left(nullptr), right(nullptr) {}
};

class AVLTree {
public:
    AVLTree() : root(nullptr) {}

    // Inserta el elemento x en el árbol AVL
    void insert(int x) {
        bool heightIncreased = false;
        insert(root, x, heightIncreased);
    }

    // Elimina el elemento x del árbol AVL (reemplazando con el predecesor si tiene dos hijos)
    void remove(int x) {
        bool heightDecreased = false;
        remove(root, x, heightDecreased);
    }

    // Recorrido inorder (lista ordenada)
    void inorder() {
        inorder(root);
        cout << endl;
    }

    // Imprime el árbol de forma visual (rotado 90°)
    void printTree() {
        printTree(root, 0);
        cout << endl;
    }

private:
    TreeNode *root;

    // ----------------------
    // Funciones de rotación
    // ----------------------
    void rotateLL(TreeNode* &p) {
        TreeNode* pB = p->left;
        p->left = pB->right;
        pB->right = p;
        p = pB;
    }

    void rotateRR(TreeNode* &p) {
        TreeNode* pB = p->right;
        p->right = pB->left;
        pB->left = p;
        p = pB;
    }

    void rotateLR(TreeNode* &p) {
        rotateRR(p->left);
        rotateLL(p);
    }

    void rotateRL(TreeNode* &p) {
        rotateLL(p->right);
        rotateRR(p);
    }

    // ---------------------------
    // Función de inserción (recursiva)
    // ---------------------------
    void insert(TreeNode* &p, int x, bool &h) {
        TreeNode *pB, *pC;
        if (p == nullptr) {
            p = new TreeNode(x);
            h = true;
        } else if (x < p->key) {
            insert(p->left, x, h);
            if (h) { // La subárbol izquierda creció
                switch (p->balance) {
                    case -1:
                        p->balance = 0;
                        h = false;
                        break;
                    case 0:
                        p->balance = +1;
                        break;
                    case +1:
                        pB = p->left;
                        if (pB->balance == +1) { // Rotación LL
                            rotateLL(p);
                            p->balance = 0;
                        } else { // Rotación LR
                            int b = pB->right->balance;
                            rotateLR(p);
                            if (b == +1)
                                p->right->balance = -1;
                            else
                                p->right->balance = 0;
                            if (b == -1)
                                p->left->balance = +1;
                            else
                                p->left->balance = 0;
                            p->balance = 0;
                        }
                        h = false;
                        break;
                }
            }
        } else if (x > p->key) {
            insert(p->right, x, h);
            if (h) { // La subárbol derecha creció
                switch (p->balance) {
                    case +1:
                        p->balance = 0;
                        h = false;
                        break;
                    case 0:
                        p->balance = -1;
                        break;
                    case -1:
                        pB = p->right;
                        if (pB->balance == -1) { // Rotación RR
                            rotateRR(p);
                            p->balance = 0;
                        } else { // Rotación RL
                            int b = pB->left->balance;
                            rotateRL(p);
                            if (b == -1)
                                p->left->balance = +1;
                            else
                                p->left->balance = 0;
                            if (b == +1)
                                p->right->balance = -1;
                            else
                                p->right->balance = 0;
                            p->balance = 0;
                        }
                        h = false;
                        break;
                }
            }
        } else { // x == p->key: elemento duplicado
            p->count++;
            h = false;
        }
    }

    // ---------------------------
    // Función de eliminación (recursiva)
    // ---------------------------
    void remove(TreeNode* &p, int x, bool &h) {
        if (p == nullptr) {
            cout << "Elemento inexistente" << endl;
            abort();
        }
        if (x < p->key) {
            remove(p->left, x, h);
            if (h)
                balanceL(p, h);
        } else if (x > p->key) {
            remove(p->right, x, h);
            if (h)
                balanceR(p, h);
        } else { // Elemento encontrado
            if (p->count > 1) {
                p->count--;
                h = false;
                return;
            }
            if (p->left == nullptr) {
                TreeNode* temp = p;
                p = p->right;
                delete temp;
                h = true;
            } else if (p->right == nullptr) {
                TreeNode* temp = p;
                p = p->left;
                delete temp;
                h = true;
            } else {
                // Usar predecesor: extraer el máximo del subárbol izquierdo
                int maxKey, maxCount;
                delMax(p->left, maxKey, maxCount, h);
                p->key = maxKey;
                p->count = maxCount;
                if (h)
                    balanceL(p, h);
            }
        }
    }

    // ---------------------------
    // Función auxiliar para eliminar el máximo (predecesor)
    // ---------------------------
    void delMax(TreeNode* &r, int &maxKey, int &maxCount, bool &h) {
        if (r->right != nullptr) {
            delMax(r->right, maxKey, maxCount, h);
            if (h)
                balanceR(r, h);
        } else {
            maxKey = r->key;
            maxCount = r->count;
            TreeNode* temp = r;
            r = r->left;
            delete temp;
            h = true;
        }
    }

    // -----------------------------------
    // Funciones de rebalanceo tras eliminación
    // -----------------------------------
    void balanceL(TreeNode* &p, bool &h) {
        TreeNode *pB, *pC;
        int balB, balC;
        switch (p->balance) {
            case +1:
                p->balance = 0;
                break;
            case 0:
                p->balance = -1;
                h = false;
                break;
            case -1:
                pB = p->right;
                balB = pB->balance;
                if (balB <= 0) { // Rotación RR
                    rotateRR(p);
                    if (balB == 0) {
                        p->balance = +1;
                        if(p->left) p->left->balance = -1;
                        h = false;
                    } else {
                        p->balance = 0;
                    }
                } else { // Rotación RL
                    pC = pB->left;
                    balC = pC->balance;
                    rotateRL(p);
                    if (balC == -1)
                        p->right->balance = +1;
                    else
                        p->right->balance = 0;
                    if (balC == +1)
                        p->left->balance = -1;
                    else
                        p->left->balance = 0;
                    p->balance = 0;
                }
                break;
        }
    }

    void balanceR(TreeNode* &p, bool &h) {
        TreeNode *pB, *pC;
        int balB, balC;
        switch (p->balance) {
            case -1:
                p->balance = 0;
                break;
            case 0:
                p->balance = +1;
                h = false;
                break;
            case +1:
                pB = p->left;
                balB = pB->balance;
                if (balB >= 0) { // Rotación LL
                    rotateLL(p);
                    if (balB == 0) {
                        p->balance = -1;
                        if(p->right) p->right->balance = +1;
                        h = false;
                    } else {
                        p->balance = 0;
                    }
                } else { // Rotación LR
                    pC = pB->right;
                    balC = pC->balance;
                    rotateLR(p);
                    if (balC == +1)
                        p->left->balance = -1;
                    else
                        p->left->balance = 0;
                    if (balC == -1)
                        p->right->balance = +1;
                    else
                        p->right->balance = 0;
                    p->balance = 0;
                }
                break;
        }
    }

    // ---------------------------
    // Recorridos e impresión
    // ---------------------------
    void inorder(TreeNode *p) {
        if (p != nullptr) {
            inorder(p->left);
            cout << p->key << "(" << p->balance << ") ";
            inorder(p->right);
        }
    }

    // Imprime el árbol de forma visual (rotado 90°)
    void printTree(TreeNode *p, int indent) {
        if (p != nullptr) {
            printTree(p->right, indent + 4);
            if (indent)
                cout << setw(indent) << " ";
            cout << p->key << "(" << p->balance << ")" << "\n";
            printTree(p->left, indent + 4);
        }
    }
};

#endif
