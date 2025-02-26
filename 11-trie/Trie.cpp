//
// Created by Guillermo Galvez on 04/02/2025.
//

#include <iostream>
using namespace std;

#define ALPHABET_SIZE 26

struct TrieNode {
    TrieNode* children[ALPHABET_SIZE]{};
    bool isEndOfWord;

    TrieNode() {
        isEndOfWord = false;
        for (auto & i : children) {
            i = nullptr;
        }
    }
};

class Trie {
private:
    TrieNode* root;


public:
    Trie() {
        root = new TrieNode();
    }

    void insert(const string& word) {
        TrieNode* node = root;
        for (char ch : word) {
            int index = ch - 'a';
            if (node->children[index] == nullptr) {
                node->children[index] = new TrieNode();
            }
            node = node->children[index];
        }
        node->isEndOfWord = true;
    }

    bool search(const string& word) {
        TrieNode* node = root;
        for (char ch : word) {
            int index = ch - 'a';
            if (node->children[index] == nullptr) {
                return false;
            }
            node = node->children[index];
        }
        return node->isEndOfWord;
    }

    bool startsWith(const string& prefix) {
        TrieNode* node = root;
        for (char ch : prefix) {
            int index = ch - 'a';
            if (node->children[index] == nullptr) {
                return false;
            }
            node = node->children[index];
        }
        return true;
    }

};

int main() {
    Trie trie;

    trie.insert("cat");
    trie.insert("car");
    trie.insert("dog");
    trie.insert("dot");

    cout << "Buscar 'cat': " << trie.search("cat") << endl;
    cout << "Buscar 'car': " << trie.search("car") << endl;
    cout << "Buscar 'cow': " << trie.search("cow") << endl;

    cout << "Prefijo 'ca': " << trie.startsWith("ca") << endl;
    cout << "Prefijo 'do': " << trie.startsWith("do") << endl;
    cout << "Prefijo 'da': " << trie.startsWith("da") << endl;

    return 0;
}