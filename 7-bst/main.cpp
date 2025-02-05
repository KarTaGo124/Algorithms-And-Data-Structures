//
// Created by Guillermo Galvez on 28/01/2025.
//

#include <iostream>
#include "BST.h"
using namespace std;

int main() {
    BinarySearchTree tree;

    // Insert nodes
    tree.root = tree.insert(tree.root, 50);
    tree.root = tree.insert(tree.root, 30);
    tree.root = tree.insert(tree.root, 70);
    tree.root = tree.insert(tree.root, 20);
    tree.root = tree.insert(tree.root, 40);
    tree.root = tree.insert(tree.root, 60);
    tree.root = tree.insert(tree.root, 80);

    // Inorder Traversal
    cout << "Inorder Traversal: ";
    tree.inorderTraversal(tree.root);
    cout << endl;

    // Preorder Traversal
    cout << "Preorder Traversal: ";
    tree.preorderTraversal(tree.root);
    cout << endl;

    // Postorder Traversal
    cout << "Postorder Traversal: ";
    tree.postorderTraversal(tree.root);
    cout << endl;

    // Search for a node
    TreeNode* searchNode = tree.search(tree.root, 40);
    cout << "Search for 40: " << (searchNode ? "Found" : "Not Found") << endl;

    // Find Min and Max
    TreeNode* minNode = tree.findMin(tree.root);
    TreeNode* maxNode = tree.findMax(tree.root);
    cout << "Min value: " << (minNode ? minNode->val : -1) << endl;
    cout << "Max value: " << (maxNode ? maxNode->val : -1) << endl;

    // Height of the tree
    cout << "Height of the tree: " << tree.height(tree.root) << endl;

    // Check if the tree is balanced
    cout << "Is the tree balanced? " << (tree.isBalanced(tree.root) ? "Yes" : "No") << endl;

    // Remove a node
    tree.root = tree.remove(tree.root, 20);
    cout << "Inorder Traversal after removing 20: ";
    tree.inorderTraversal(tree.root);
    cout << endl;

    tree.root = tree.remove(tree.root, 50);
    tree.root = tree.remove(tree.root, 30);

    cout << "Inorder Traversal after removing 50: ";
    tree.inorderTraversal(tree.root);
    cout << endl;

    // Check if the tree is balanced
    cout << "Is the tree balanced? " << (tree.isBalanced(tree.root) ? "Yes" : "No") << endl;

    // DFS Traversal
    cout << "DFS Traversal: ";
    tree.DFS(tree.root);
    cout << endl;

    // BFS Traversal
    cout << "BFS Traversal: ";
    tree.BFS(tree.root);
    cout << endl;

    // Clear the tree
    tree.clear(tree.root);
    cout << "Tree cleared. Is the tree empty? " << (tree.isEmpty(tree.root) ? "Yes" : "No") << endl;

    return 0;
}