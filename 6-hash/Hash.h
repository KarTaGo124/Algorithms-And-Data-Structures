#ifndef ALGORITHMS_AND_DATA_STRUCTURES_HASH_H
#define ALGORITHMS_AND_DATA_STRUCTURES_HASH_H

#include <iostream>
#include <vector>
using namespace std;

template <typename T, typename Q>
struct Node {
    T key;
    Q value;
    Node* next;
    Node(T k, Q v) : key(k), value(v), next(nullptr) {}
};

static const int SIZE = 10000;

template <typename T>
int hashFunction(const T& key) {
    return hash<T>()(key) % SIZE;
}

int hashFunctionInt(int key) {
    return key % SIZE;
}

int hashFunctionChar(const char key) {
    int hash = 0;
    hash = (hash * 31 + key) % SIZE;
    return hash;
}

int hashFunctionString(const string& key) {
    int hash = 0;
    for (char c: key) {
        hash = (hash * 31 + c) % SIZE;
    }
    return hash;
}


template <typename T, typename Q>
class Hash {
private:
    Node<T,Q>* buckets[SIZE]{};

public:
    Hash() {
        for (auto & bucket : buckets) {
            bucket = nullptr;
        }
    }

    ~Hash() {
        for (auto current : buckets) {
            while (current != nullptr) {
                auto temp = current;
                current = current->next;
                delete temp;
            }
        }
    }


    void put(T key, Q value) {
        int index = hashFunction(key);
        auto current = buckets[index];
        while (current != nullptr) {
            if (current->key == key) {
                current->value = value;
                return;
            }
            current = current->next;
        }
        auto newNode = new Node<T,Q>(key, value);
        newNode->next = buckets[index];
        buckets[index] = newNode;
    }

    Q get(T key) {
        int index = hashFunction(key);
        auto current = buckets[index];
        while (current != nullptr) {
            if (current->key == key) {
                return current->value;
            }
            current = current->next;
        }
        return Q{};
    }

    void remove(T key) {
        int index = hashFunction(key);
        auto current = buckets[index];
        Node<T,Q>* prev = nullptr;
        while (current != nullptr) {
            if (current->key == key) {
                if (prev != nullptr) {
                    prev->next = current->next;
                } else {
                    buckets[index] = current->next;
                }
                delete current;
                return;
            }
            prev = current;
            current = current->next;
        }
    }

    bool find(T key) {
        return get(key) != Q{};
    }

    bool findValue(Q value) {
        for (auto current : buckets) {
            while (current != nullptr) {
                if (current->value == value) {
                    return true;
                }
                current = current->next;
            }
        }
        return false;
    }

    int size() {
        int count = 0;
        for (auto current : buckets) {
            while (current != nullptr) {
                count++;
                current = current->next;
            }
        }
        return count;
    }

    void clear() {
        for (auto & bucket : buckets) {
            auto current = bucket;
            while (current != nullptr) {
                auto temp = current;
                current = current->next;
                delete temp;
            }
            bucket = nullptr;
        }
    }

    vector<T> getAllKeys() {
        vector<T> keys;
        for (auto current : buckets) {
            while (current != nullptr) {
                keys.push_back(current->key);
                current = current->next;
            }
        }
        return keys;
    }

    vector<Q> getAllValues() {
        vector<Q> values;
        for (auto current : buckets) {
            while (current != nullptr) {
                values.push_back(current->value);
                current = current->next;
            }
        }
        return values;
    }
};

#endif // ALGORITHMS_AND_DATA_STRUCTURES_HASH_H
