//
// Created by Guillermo Galvez on 23/02/2025.
//

#include "AVLTree.h"

int main() {
    AVLTree tree;

    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(7);
    tree.insert(12);
    tree.insert(17);
    tree.insert(1);
    tree.insert(4);
    tree.insert(6);
    tree.insert(8);
    tree.insert(11);
    tree.insert(13);
    tree.insert(16);
    tree.insert(18);

    tree.printTree();

    tree.remove(5);

    cout << "---------------------" << endl;
    tree.printTree();

    tree.remove(15);
    cout << "---------------------" << endl;
    tree.printTree();

    tree.remove(10);

    cout << "---------------------" << endl;
    tree.printTree();

    return 0;
}