//
// Created by Rohit Sharma on 12/03/24.
//
#include <iostream>
#include <vector>
#include <algorithm>
#include "Heap.h"
#include "MemoryBlock.h"
#include "MemoryBlock.cpp"

class Heap {
private:
    // Stores information about all memory blocks
    // Maximum heap size for demo purposes
    size_t usedMemory = 0; // Tracks the amount of used memory

public:
    void* allocate(size_t size) {
        if (usedMemory + size > MAX_HEAP_SIZE) {
            std::cout << "Allocation failed: Not enough memory.\n";
            return nullptr; // Allocation failure code
        }

        // Simulate memory allocation (for demo purposes, we don't use real memory allocation)
        void* segmentAddress = reinterpret_cast<void*>(usedMemory);
        blocks.emplace_back(size, segmentAddress);
        usedMemory += size;

        std::cout << "Allocated " << size << " bytes. Total used memory: " << usedMemory << " bytes.\n";
        return segmentAddress;
    }

    void free(void* segmentAddress) {
        auto it = std::find_if(blocks.begin(), blocks.end(), [segmentAddress](const MemoryBlock& block) {
            return block.segmentAddress == segmentAddress;
        });

        if (it != blocks.end()) {
            it->inUse = false;
            std::cout << "Freed memory block at " << it->segmentAddress << ". Size: " << it->size << " bytes.\n";
        } else {
            std::cout << "Free failed: No matching memory block found.\n";
        }
    }

    void logMemoryUsage() {
        std::cout << "\nMemory Usage Report:\n";
        std::cout << "Total memory reserved: " << MAX_HEAP_SIZE << " bytes\n";
        std::cout << "Total memory used: " << usedMemory << " bytes\n";
        for (const auto& block : blocks) {
            std::cout << "Block at " << block.segmentAddress << " - Size: " << block.size << " bytes, Status: " << (block.inUse ? "In Use" : "Not In Use") << "\n";
        }
    }

    const size_t MAX_HEAP_SIZE = 1024 * 1024;
    std::vector<MemoryBlock> blocks;
};