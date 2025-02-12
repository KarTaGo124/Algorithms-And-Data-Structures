#ifndef ALGORITHMS_AND_DATA_STRUCTURES_HASH_H
#define ALGORITHMS_AND_DATA_STRUCTURES_HASH_H

#include "../2-linked-list/ForwardList.h"

#define SIZE 100000

template <typename T, typename Q>
struct HashNode {
    T key;
    Q value;
    HashNode* next;
    HashNode(T k, Q v) : key(k), value(v), next(nullptr) {}
};

template <typename T>
int hashFunction(const T& key) {
    return hash<T>()(key) % SIZE;
}

template <typename T, typename Q>
class Hash {
private:
    HashNode<T,Q>* buckets[SIZE]{};

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
        auto newNode = new HashNode<T,Q>(key, value);
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

    const Q& operator[](const T& key) const {
        int index = hashFunction(key);
        auto current = buckets[index];
        while (current != nullptr) {
            if (current->key == key) {
                return current->value;
            }
            current = current->next;
        }
        throw std::out_of_range("Key not found");
    }

    Q& operator[](const T& key) {
        int index = hashFunction(key);
        auto current = buckets[index];
        while (current != nullptr) {
            if (current->key == key) {
                return current->value;
            }
            current = current->next;
        }
        // If the key does not exist, insert a new node with a default value
        auto newNode = new HashNode<T, Q>(key, Q{});
        newNode->next = buckets[index];
        buckets[index] = newNode;
        return buckets[index]->value;
    }

    void remove(T key) {
        int index = hashFunction(key);
        auto current = buckets[index];
        HashNode<T,Q>* prev = nullptr;
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

    bool exists(T key) {
        int index = hashFunction(key);
        auto current = buckets[index];
        while (current != nullptr) {
            if (current->key == key) {
                return true;
            }
            current = current->next;
        }
        return false;
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

    ForwardList<T> getAllKeys() {
        ForwardList<T> keys;
        for (auto current : buckets) {
            while (current != nullptr) {
                keys.push_back(current->key);
                current = current->next;
            }
        }
        return keys;
    }

    ForwardList<Q> getAllValues() {
        ForwardList<Q> values;
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
