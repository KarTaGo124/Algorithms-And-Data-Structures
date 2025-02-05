//
// Created by Guillermo Galvez on 28/01/2025.
//

#ifndef ALGORITHMS_AND_DATA_STRUCTURES_BST_H
#define ALGORITHMS_AND_DATA_STRUCTURES_BST_H

#include <iostream>
#include <queue>
#include <stack>
using namespace std;


struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class BinarySearchTree {
public:
    TreeNode* root;

    BinarySearchTree() : root(nullptr) {}

    TreeNode* insert(TreeNode* root, int val) {
        if (!root) return new TreeNode(val);
        if (val < root->val) root->left = insert(root->left, val);
        else root->right = insert(root->right, val);
        return root;
    }

    TreeNode* findMin(TreeNode* root) {
        while (root && root->left) root = root->left;
        return root;
    }

    TreeNode* remove(TreeNode* root, int val) {
        if (!root) return nullptr;
        if (val < root->val) root->left = remove(root->left, val);
        else if (val > root->val) root->right = remove(root->right, val);
        else {
            if (!root->left && !root->right) { // Caso 1: Nodo hoja
                delete root;
                return nullptr;
            }
            else if (!root->left) { // Caso 2: Un solo hijo derecho
                TreeNode* temp = root->right;
                delete root;
                return temp;
            }
            else if (!root->right) { // Caso 2: Un solo hijo izquierdo
                TreeNode* temp = root->left;
                delete root;
                return temp;
            }
            else { // Caso 3: Dos hijos
                TreeNode* temp = findPredecessor(root, root);
                root->val = temp->val;
                root->left = remove(root->left, temp->val);
            }
        }
        return root;
    }

    TreeNode* search(TreeNode* root, int val) {
        if (!root || root->val == val) return root;
        return val < root->val ? search(root->left, val) : search(root->right, val);
    }

    TreeNode* findMax(TreeNode* root) {
        while (root && root->right) root = root->right;
        return root;
    }

    void inorderTraversal(TreeNode* root) {
        if (!root) return;
        inorderTraversal(root->left);
        printf("%d ", root->val);
        inorderTraversal(root->right);
    }

    void preorderTraversal(TreeNode* root) {
        if (!root) return;
        printf("%d ", root->val);
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }

    void postorderTraversal(TreeNode* root) {
        if (!root) return;
        postorderTraversal(root->left);
        postorderTraversal(root->right);
        printf("%d ", root->val);
    }

    int height(TreeNode* root) {
        if (!root) return -1;
        return 1 + std::max(height(root->left), height(root->right));
    }

    bool isBalanced(TreeNode* root) {
        if (!root) return true;
        int lh = height(root->left), rh = height(root->right);
        return abs(lh - rh) <= 1 && isBalanced(root->left) && isBalanced(root->right);
    }

    TreeNode* findSuccessor(TreeNode* root, TreeNode* node) {
        if (node->right) return findMin(node->right);
        TreeNode* succ = nullptr;
        while (root) {
            if (node->val < root->val) {
                succ = root;
                root = root->left;
            } else if (node->val > root->val) root = root->right;
            else break;
        }
        return succ;
    }

    TreeNode* findPredecessor(TreeNode* root, TreeNode* node) {
        if (node->left) return findMax(node->left);
        TreeNode* pred = nullptr;
        while (root) {
            if (node->val > root->val) {
                pred = root;
                root = root->right;
            } else if (node->val < root->val) root = root->left;
            else break;
        }
        return pred;
    }

    void clear(TreeNode*& root) {
        if (!root) return;
        clear(root->left);
        clear(root->right);
        delete root;
        root = nullptr;
    }

    bool isEmpty(TreeNode* root) {
        return root == nullptr;
    }

    void DFS(TreeNode* root) {
        if (!root) return;
        std::stack<TreeNode*> s;
        s.push(root);
        while (!s.empty()) {
            TreeNode* node = s.top(); s.pop();
            printf("%d ", node->val);
            if (node->right) s.push(node->right);
            if (node->left) s.push(node->left);
        }
    }

    void BFS(TreeNode* root) {
        if (!root) return;
        std::queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            TreeNode* node = q.front(); q.pop();
            printf("%d ", node->val);
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
    }
};



#endif //ALGORITHMS_AND_DATA_STRUCTURES_BST_H
