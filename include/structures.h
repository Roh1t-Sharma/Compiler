//
// Created by Rohit Sharma on 26/03/24.
//

#ifndef MEMORYMANGER_STRUCTURES_H
#define MEMORYMANGER_STRUCTURES_H

#include <iostream>
#include <utility>
#include <memory> // For std::allocator

struct HashNode {
    std::string key;
    std::string id;
    int count;
    HashNode* next;

    HashNode(std::string key, std::string id) : key(key), id(id), count(1), next(nullptr) {}
};



#endif //MEMORYMANGER_STRUCTURES_H
