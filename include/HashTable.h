//
// Created by Rohit Sharma on 26/03/24.
//

#ifndef MEMORYMANGER_HASHTABLE_H
#define MEMORYMANGER_HASHTABLE_H

#include <iostream>
#include <vector>
#include <algorithm>
#include "structures.h"
#include "../src/Heap.cpp"
#include <memory> // For std::allocator
#include <chrono>
#include <sstream>

class HashTable {
private:
    static const int TABLE_SIZE = 10;
    HashNode** table;
    std::allocator<HashNode> allocator;

    static int hashFunction(std::string key) {
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
        for (int i = 0; i < TABLE_SIZE; ++i) {
            HashNode* entry = table[i];
            while (entry) {
                HashNode* prev = entry;
                entry = entry->next;
                allocator.destroy(prev);
                allocator.deallocate(prev, 1);
            }
        }
        delete[] table;
    }

    void insert(std::string key, std::string id = "") {
        if (id.empty()) {
            // Generate a unique ID if not provided
            id = generateUniqueId(key);
        }
        int hashValue = hashFunction(key);
        HashNode* newNode = allocator.allocate(1);
        allocator.construct(newNode, HashNode(key, id));
        newNode->next = table[hashValue];
        table[hashValue] = newNode;
    }

    std::string get(std::string key) {
        int hashValue = hashFunction(key);
        HashNode* entry = table[hashValue];
        while (entry) {
            if (entry->key == key) {
                return entry->id; // Return the most recent ID for the key
            }
            entry = entry->next;
        }
        return ""; // Key not found
    }

    void displayTable() {
        std::cout << "Hash Table Contents:\n";
        for (int i = 0; i < TABLE_SIZE; ++i) {
            HashNode* entry = table[i];
            std::cout << "[" << i << "]";
            while (entry != nullptr) {
                std::cout << " -> [" << entry->key << " : " << entry->id << "]";
                entry = entry->next;
            }
            std::cout << std::endl;
        }
    }

    void logMemoryUsage() {
        size_t totalMemory = 0;
        size_t nodeCount = 0;

        // Each HashNode memory
        for (int i = 0; i < TABLE_SIZE; ++i) {
            HashNode* entry = table[i];
            while (entry != nullptr) {
                totalMemory += sizeof(HashNode);
                nodeCount++;
                entry = entry->next;
            }
        }

        // Memory used by the table array itself
        totalMemory += TABLE_SIZE * sizeof(HashNode*);

        std::cout << "\nHash Table Memory Usage Report:\n";
        std::cout << "Total HashNodes: " << nodeCount << "\n";
        std::cout << "Total memory used by nodes: " << totalMemory << " bytes\n";
        std::cout << "Memory used by table array: " << TABLE_SIZE * sizeof(HashNode*) << " bytes\n";
        std::cout << "Total memory used: " << totalMemory + (TABLE_SIZE * sizeof(HashNode*)) << " bytes\n";
    }

private:
    static std::string generateUniqueId(const std::string& key) {
        auto now = std::chrono::system_clock::now();
        auto now_ms = std::chrono::time_point_cast<std::chrono::hours>(now);
        auto value = now_ms.time_since_epoch();
        long duration = value.count();
        std::stringstream ss;
        ss << "Key assigned to " << key << " – " << duration;
        return ss.str();
    }
};


#endif //MEMORYMANGER_HASHTABLE_H
