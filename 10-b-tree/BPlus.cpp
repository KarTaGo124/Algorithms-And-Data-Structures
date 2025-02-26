#include <iostream>
using namespace std;

class BPlusTreeNode {
    int *keys;
    int t;
    BPlusTreeNode **C;
    int n;
    bool leaf;
    BPlusTreeNode *next;
public:
    BPlusTreeNode(int _t, bool _leaf) {
        t = _t;
        leaf = _leaf;
        keys = new int[2 * t - 1];
        C = new BPlusTreeNode*[2 * t];
        n = 0;
        next = nullptr;
    }
    void insertNonFull(int k) {
        int i = n - 1;
        if(leaf) {
            while(i >= 0 && keys[i] > k) {
                keys[i+1] = keys[i];
                i--;
            }
            keys[i+1] = k;
            n++;
        } else {
            while(i >= 0 && keys[i] > k)
                i--;
            if(C[i+1]->n == 2*t - 1) {
                splitChild(i+1, C[i+1]);
                if(keys[i+1] <= k)
                    i++;
            }
            C[i+1]->insertNonFull(k);
        }
    }
    void splitChild(int i, BPlusTreeNode *y) {
        BPlusTreeNode *z = new BPlusTreeNode(y->t, y->leaf);
        int mid;
        if(y->leaf) {
            mid = (y->n + 1) / 2;
            for(int j = 0; j < y->n - mid; j++)
                z->keys[j] = y->keys[j+mid];
            z->n = y->n - mid;
            y->n = mid;
            z->next = y->next;
            y->next = z;
            for(int j = n; j >= i+1; j--)
                C[j+1] = C[j];
            C[i+1] = z;
            for(int j = n-1; j >= i; j--)
                keys[j+1] = keys[j];
            keys[i] = z->keys[0];
            n++;
        } else {
            mid = y->n / 2;
            for(int j = 0; j < y->n - mid - 1; j++)
                z->keys[j] = y->keys[j+mid+1];
            for(int j = 0; j < y->n - mid; j++)
                z->C[j] = y->C[j+mid+1];
            z->n = y->n - mid - 1;
            int up = y->keys[mid];
            y->n = mid;
            for(int j = n; j >= i+1; j--)
                C[j+1] = C[j];
            C[i+1] = z;
            for(int j = n-1; j >= i; j--)
                keys[j+1] = keys[j];
            keys[i] = up;
            n++;
        }
    }
    void traverse() {
        if(leaf) {
            for(int i = 0; i < n; i++)
                cout << keys[i] << " ";
        } else {
            for(int i = 0; i < n; i++) {
                C[i]->traverse();
                cout << keys[i] << " ";
            }
            C[n]->traverse();
        }
    }
    void printTree(int level) {
        for(int i = 0; i < level; i++)
            cout << "   ";
        cout << "[ ";
        for(int i = 0; i < n; i++)
            cout << keys[i] << " ";
        cout << "]" << endl;
        if(!leaf) {
            for(int i = 0; i <= n; i++)
                if(C[i])
                    C[i]->printTree(level+1);
        }
    }
    BPlusTreeNode* search(int k) {
        int i = 0;
        while(i < n && k > keys[i])
            i++;
        if(leaf) {
            if(i < n && keys[i] == k)
                return this;
            return nullptr;
        }
        return C[i]->search(k);
    }
    void remove(int k) {
        if(leaf) {
            int idx = 0;
            while(idx < n && keys[idx] < k)
                idx++;
            if(idx < n && keys[idx] == k)
                removeFromLeaf(idx);
            else
                cout << "Key " << k << " not found.\n";
            return;
        } else {
            int idx = 0;
            while(idx < n && k > keys[idx])
                idx++;
            if(C[idx]->n < t)
                fill(idx);
            if(idx < n && keys[idx] < k)
                C[idx+1]->remove(k);
            else
                C[idx]->remove(k);
        }
    }
    void removeFromLeaf(int idx) {
        for(int i = idx; i < n-1; i++)
            keys[i] = keys[i+1];
        n--;
    }
    void fill(int idx) {
        if(idx != 0 && C[idx-1]->n > t-1)
            borrowFromPrev(idx);
        else if(idx != n && C[idx+1]->n > t-1)
            borrowFromNext(idx);
        else {
            if(idx != n)
                merge(idx);
            else
                merge(idx-1);
        }
    }
    void borrowFromPrev(int idx) {
        BPlusTreeNode *child = C[idx];
        BPlusTreeNode *sibling = C[idx-1];
        if(child->leaf) {
            for(int i = child->n-1; i >= 0; i--)
                child->keys[i+1] = child->keys[i];
            child->keys[0] = sibling->keys[sibling->n-1];
            keys[idx-1] = child->keys[0];
            child->n++;
            sibling->n--;
        } else {
            for(int i = child->n-1; i >= 0; i--)
                child->keys[i+1] = child->keys[i];
            child->keys[0] = keys[idx-1];
            for(int i = child->n; i >= 0; i--)
                child->C[i+1] = child->C[i];
            child->C[0] = sibling->C[sibling->n];
            keys[idx-1] = sibling->keys[sibling->n-1];
            child->n++;
            sibling->n--;
        }
    }
    void borrowFromNext(int idx) {
        BPlusTreeNode *child = C[idx];
        BPlusTreeNode *sibling = C[idx+1];
        if(child->leaf) {
            child->keys[child->n] = sibling->keys[0];
            for(int i = 1; i < sibling->n; i++)
                sibling->keys[i-1] = sibling->keys[i];
            keys[idx] = sibling->keys[0];
            child->n++;
            sibling->n--;
        } else {
            child->keys[child->n] = keys[idx];
            child->C[child->n+1] = sibling->C[0];
            keys[idx] = sibling->keys[0];
            for(int i = 1; i < sibling->n; i++)
                sibling->keys[i-1] = sibling->keys[i];
            for(int i = 1; i <= sibling->n; i++)
                sibling->C[i-1] = sibling->C[i];
            child->n++;
            sibling->n--;
        }
    }
    void merge(int idx) {
        BPlusTreeNode *child = C[idx];
        BPlusTreeNode *sibling = C[idx+1];
        if(child->leaf) {
            for(int i = 0; i < sibling->n; i++)
                child->keys[child->n+i] = sibling->keys[i];
            child->n += sibling->n;
            child->next = sibling->next;
            for(int i = idx+1; i < n; i++)
                keys[i-1] = keys[i];
            for(int i = idx+2; i <= n; i++)
                C[i-1] = C[i];
            n--;
            delete sibling;
        } else {
            child->keys[child->n] = keys[idx];
            for(int i = 0; i < sibling->n; i++)
                child->keys[i+child->n+1] = sibling->keys[i];
            for(int i = 0; i <= sibling->n; i++)
                child->C[i+child->n+1] = sibling->C[i];
            child->n += sibling->n + 1;
            for(int i = idx+1; i < n; i++)
                keys[i-1] = keys[i];
            for(int i = idx+2; i <= n; i++)
                C[i-1] = C[i];
            n--;
            delete sibling;
        }
    }
    BPlusTreeNode* getFirstLeaf() {
        BPlusTreeNode *cur = this;
        while(!cur->leaf)
            cur = cur->C[0];
        return cur;
    }
    friend class BPlusTree;
};

class BPlusTree {
    BPlusTreeNode *root;
    int t;
public:
    BPlusTree(int _t) { root = nullptr; t = _t; }
    void traverse() { if(root) root->traverse(); }
    void printTree() { if(root){ cout << "B+ Tree structure:" << endl; root->printTree(0); } }
    void printLeaves() {
        if(!root) return;
        BPlusTreeNode *cur = root;
        while(!cur->leaf)
            cur = cur->C[0];
        cout << "Leaf level: ";
        while(cur) {
            for(int i = 0; i < cur->n; i++)
                cout << cur->keys[i] << " ";
            cur = cur->next;
        }
        cout << endl;
    }
    BPlusTreeNode* search(int k) { return (root==nullptr)?nullptr:root->search(k); }
    void insert(int k) {
        if(!root) {
            root = new BPlusTreeNode(t, true);
            root->keys[0] = k;
            root->n = 1;
        } else {
            if(root->n == 2*t - 1) {
                BPlusTreeNode *s = new BPlusTreeNode(t, false);
                s->C[0] = root;
                s->splitChild(0, root);
                int i = (s->keys[0] <= k) ? 1 : 0;
                s->C[i]->insertNonFull(k);
                root = s;
            } else {
                root->insertNonFull(k);
            }
        }
    }
    void remove(int k) {
        if(!root) {
            cout << "The tree is empty\n";
            return;
        }
        root->remove(k);
        if(root->n == 0) {
            BPlusTreeNode *tmp = root;
            if(root->leaf)
                root = nullptr;
            else
                root = root->C[0];
            delete tmp;
        }
    }
};

int main() {
    BPlusTree tree(3);
    tree.insert(10);
    tree.insert(20);
    tree.insert(5);
    tree.insert(6);
    tree.insert(12);
    tree.insert(30);
    tree.insert(7);
    tree.insert(17);

    cout << "Before deletion:" << endl;
    tree.printTree();
    tree.printLeaves();

    tree.remove(10);
    cout << "\nAfter deleting 10:" << endl;
    tree.printTree();
    tree.printLeaves();

    tree.remove(6);
    cout << "\nAfter deleting 6:" << endl;
    tree.printTree();
    tree.printLeaves();

    tree.insert(40);
    tree.insert(50);

    cout << "\nAfter inserting 40 and 50:" << endl;
    tree.printTree();
    tree.printLeaves();

    tree.remove(12);
    cout << "\nAfter deleting 12:" << endl;
    tree.printTree();
    tree.printLeaves();



    return 0;
}
