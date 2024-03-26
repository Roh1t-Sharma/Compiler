//
// Created by Rohit Sharma on 26/03/24.
//

#ifndef MEMORYMANGER_HASHTABLE_H
#define MEMORYMANGER_HASHTABLE_H

#include <iostream>
#include <vector>
#include <algorithm>
#include "structures.h"

class HashTable {
private:
    static const int TABLE_SIZE = 10; // Simplified for demonstration
    HashNode** table;

    int hashFunction(std::string key) {
        // Simple hash function: sum of characters modulo table size
        int sum = 0;
        for (char ch : key) {
            sum += ch;
        }
        return sum % TABLE_SIZE;
    }

public:
    HashTable() {
        table = new HashNode*[TABLE_SIZE]();
    }

    ~HashTable() {
        // Destructor to free memory
        for (int i = 0; i < TABLE_SIZE; ++i) {
            HashNode* entry = table[i];
            while (entry) {
                HashNode* prev = entry;
                entry = entry->next;
                delete prev;
            }
        }
        delete[] table;
    }

    void insert(std::string key) {
        int hashValue = hashFunction(key);
        HashNode* prev = nullptr;
        HashNode* entry = table[hashValue];

        while (entry != nullptr) {
            prev = entry;
            entry = entry->next;
        }

        if (entry == nullptr) {
            entry = new HashNode(key);
            if (prev == nullptr) {
                // Insert as first bucket
                table[hashValue] = entry;
            } else {
                prev->next = entry;
            }
        } else {
            // Handle update scenario (if needed)
        }
    }

    void displayTable() {
        std::cout << "Hash Table Contents:\n";
        for (int i = 0; i < TABLE_SIZE; ++i) {
            HashNode* entry = table[i];
            std::cout << "[" << i << "]";
            while (entry != nullptr) {
                std::cout << " -> " << entry->key;
                entry = entry->next;
            }
            std::cout << std::endl;
        }
    }
};



#endif //MEMORYMANGER_HASHTABLE_H
