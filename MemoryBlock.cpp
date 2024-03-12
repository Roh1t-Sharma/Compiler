//
// Created by Rohit Sharma on 12/03/24.
//
#include <iostream>
#include <vector>
#include <algorithm>
#include "MemoryBlock.h"
struct MemoryBlock {
    size_t size; // Size of the block
    bool inUse; // Whether the block is in use or not
    void* segmentAddress; // Address of the block in the heap

    MemoryBlock(size_t sz, void* addr) : size(sz), inUse(true), segmentAddress(addr) {}
};