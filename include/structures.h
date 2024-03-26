//
// Created by Rohit Sharma on 26/03/24.
//

#ifndef MEMORYMANGER_STRUCTURES_H
#define MEMORYMANGER_STRUCTURES_H

#include <iostream>
struct HashNode {
    std::string key;
    HashNode* next;

    HashNode(std::string key) : key(key), next(nullptr) {}
};

#endif //MEMORYMANGER_STRUCTURES_H
