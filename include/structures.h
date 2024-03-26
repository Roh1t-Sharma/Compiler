//
// Created by Rohit Sharma on 26/03/24.
//

#ifndef MEMORYMANGER_STRUCTURES_H
#define MEMORYMANGER_STRUCTURES_H

#include <iostream>
#include <utility>
struct HashNode {
    std::string key;
    HashNode* next;

    explicit HashNode(std::string key) : key(std::move(key)), next(nullptr) {}
};

#endif //MEMORYMANGER_STRUCTURES_H
